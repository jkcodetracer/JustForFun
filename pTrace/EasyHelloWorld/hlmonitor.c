/*
 * @FileName: hlmonitor.c
 * @Author: wzj
 * @Brief: 
 *  1. 使用ptrace来跟踪目标程序 
 *  2. 获取参数，修改参数 (系统调用，都使用寄存器传参数，恩...)
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年06月24日星期日20:21:32
 * 
 */ 
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **map = NULL;
int maplen = 0;
const static LONG_LEN = sizeof(long);

int
paserline(char *linebuf, int *calnum, char** pcalname)
{
	if(linebuf == NULL)	
	{
		return -1;
	}
	
	char calnumarray[5] = {'\0'};
	int j = 0, i = 0;
	char *ret = strstr(linebuf, "__NR_");
	if(ret == NULL)
	{
		return -1;
	}

	//改成空格段解析模块比较好，先用这
	*pcalname = ret;
	while(*ret != '\0')
	{
		i++;
		if(*ret != ' ' && *ret != '\t')
		{	
			ret ++;
			continue;
		}
		
		while((*ret == ' ' || *ret == '\t') && (*ret != '\0'))
		{
			*ret = '\0';
			ret ++;
		}
		//#define __NR_exit   1  是这么回事 要获取到1
		while((*ret >= '0' && *ret <= '9') && *ret != '\0')	
		{
			calnumarray[j] = *ret;	
			j++;
			ret ++;
		}
	}

	if(j > 0)
	{
		*calnum = 0;
		i = 0;
		while(i < j)	
		{
			*calnum = (*calnum) * 10 + calnumarray[i] - '0';	
			i++;
		}
	}

	return 0;
}
//映射系统调用名字和编号
int
call_map_init()
{
	if(map == NULL)	
	{
		map = (char**) malloc(sizeof(char*) * 10); 
		if(map == NULL)
		{
			return -1;
		}
		maplen = 10;
	}

	char linebuf[128] = {'\0'};
	char *calname = NULL;
	int calnum = 0;
	FILE *fp = fopen("./unistd_32.h", "r");
	if(fp == NULL)
	{
		return -1;
	}

	while(fgets(linebuf, sizeof(linebuf), fp) != NULL)
	{
		linebuf[sizeof(linebuf) - 1] = '\0';
		calnum = 0;
		int ret = paserline(linebuf, &calnum, &calname);	
		if(ret != 0)
		{
//			printf("failed line: %s\n", linebuf);
			memset(linebuf,  0, sizeof(linebuf));
			continue;
		}
		if(calname == NULL)		
		{
			memset(linebuf,  0, sizeof(linebuf));
			continue;
		}
		if(calnum >= maplen)
		{
			char **tmpmap = (char**) realloc(map, (calnum + 1) * sizeof(char*));	
			if(tmpmap == NULL)
			{
				printf("realloc failed!\n");
				fclose(fp);
				return -1;	
			}
			map = tmpmap;
			maplen = calnum + 1;
		}
		int calnmlen = strlen(calname);	
		char *newcal = (char*) malloc((calnmlen + 1) * sizeof(char));
		if(newcal == NULL)
		{
			printf("malloc new call failed \n");
			fclose(fp);
			return -1;
		}
		strcpy(newcal, calname);
		map[calnum] = newcal;
		memset(linebuf,  0, sizeof(linebuf));
	}
	if(fp)
		fclose(fp);
	return 0;	
}
//全部修改掉
int 
putdata(pid_t child, long addr, char* str, long len)
{
	union u{
		long data;
		char chrstr[LONG_LEN];
	}data;
	
	char *laddr = str;
	int i = 0;
	int j = 0;
	for(; i < len; i++)
	{
		str[i] = toupper(str[i]);
	}
	printf("%s\n", str);

	i = 0;
	j =	len / LONG_LEN; 
	//写也是一样的，都要老老实实地对齐了写	
	while(i < j)
	{
		memcpy(data.chrstr, laddr, LONG_LEN);
		ptrace(PTRACE_POKEDATA, child,
				addr + i * 4, data.data);	
		laddr += LONG_LEN;
		i++;
	}

	j = len % LONG_LEN;
	if(j != 0) 
	{
		memcpy(data.chrstr, laddr, j);
		ptrace(PTRACE_POKEDATA, child, 
				addr + i * 4, data.data);	
	}

	return 0;
}
//获取用户空间的数据
int
getdata(pid_t child, long addr, char* str, long len)
{
	union u{
		long data;
		char chr_array[LONG_LEN];
	}data;	

	int i = 0;
	int j = len/LONG_LEN;
	char *laddr = str;
	//为什么一次只读取4个字节？
	//堆栈一般以4字节对齐，ptrace应该是这样想的,所以PEEKDATA的时候，一次
	//也只peek4个字节的
	while(i < j)
	{
		data.data = ptrace(PTRACE_PEEKDATA,
						child, addr + i * 4, NULL);
		memcpy(laddr, data.chr_array, LONG_LEN);
		i++;
		laddr += LONG_LEN;
	}

	j = len % LONG_LEN;
	if (j != 0)
	{ //不用考虑大小端的问题?
		data.data = ptrace(PTRACE_PEEKDATA,
						child, addr + i * 4, NULL);	
		memcpy(laddr, data.chr_array, j);
	}

	str[len] = '\0';

	return 0;
}

int
main()
{
	pid_t child;
	int status;
	long orig_eax;
	struct user_regs_struct  regs;
	int i = 0;
	//映射系统调用名字和系统调用号,头文件里面有一些是
	//宏展开的，这里没有处理
	call_map_init();	
//	for(i = 0; i < maplen;i++)
//	{
//		if(map[i] != NULL)
//		printf("%s\n", map[i]);
//	}
//
	child = fork();
	if(child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("./a.out", "./a.out", NULL);
		//没什么必要了，不会返回的。
		exit(0);
	} else {
		long param[3] = {0};
		struct user_regs_struct regs; //把寄存器的值掏出来。
		int start = 0;
		long ins = 0;
		int toggle = 0;

		while(1)
		{
			wait(&status);
			if(WIFEXITED(status))
			{
				break;
			}
			orig_eax = ptrace(PTRACE_PEEKUSER,
							  child, 4 * ORIG_EAX, NULL);	
			//把寄存器值掏出来
			ptrace(PTRACE_GETREGS, child, NULL, &regs);

			if(start == 1){ //看看每一步都做了什么
				ins = ptrace(PTRACE_PEEKTEXT,
						child, regs.eip, NULL);	
				printf("EIP: %lx Instruction "
						"executed:%lx \n",
						regs.eip, ins);
			}
			//大多数系统调用会两次进入这个流程，初步猜想，是应为调用和返回，造成这种现象。
			//而在系统调用第二次进入时，调用PTRACE_SINGLESTEP会导致coredump
			//SYS_execve不能使用单步，一进入就coredump。
			//SYS_close和SYS_execve都只有一次调用，没有第二次调用。特殊的系统调用，而且
			//SYS_close对单步无动于衷。
			//if(orig_eax == SYS_close)
			if(orig_eax != SYS_execve)
			{
				if(start == 0)
				{	//开始单步
					start = 1;
					param[0] = ptrace(PTRACE_PEEKUSER,
									  child, 4 * EBX, NULL);			
					param[1] = ptrace(PTRACE_PEEKUSER,
							  child, 4 * ECX, NULL);
					param[2] = ptrace(PTRACE_PEEKUSER,
									  child, 4 * EDX, NULL);
						char *str = (char*)malloc((param[2]+1) * sizeof(char));	
						if(str != NULL)
						{
							getdata(child, param[1],
									str, param[2]);
		//					printf("-----%s------\n", str);
		//					putdata(child, param[1],
		//							str, param[2]);
							char *tmp = "hello WORLD\n";
							//换掉寄存器里面的值，指向新的字符串
							//这样修改寄存器的值没有用，
							//ecx 里面存放的是用户空间的一个地址，虽然换掉了，但是结果是什么也不
							//输出了，修改edx的时候，减小数只能让他多打印几次，最后还是全部都打印完毕了
							//看来printf的实现是循环读写的~
							//regs.ecx = tmp;
		//					ptrace(PTRACE_SETREGS, child, NULL, &regs);
						}
						free(str);
						str = NULL;
				} else {
					start = 0;
				}
			}
			printf("current call: %ld : call name: %s\n", orig_eax, map[(int)orig_eax]);
		
			if(start == 1)
			{
				//不知道为什么，连续调用会coredump
				ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
			} else {
				//返回继续系统调用
				start = 0;
				ptrace(PTRACE_SYSCALL, child, NULL, NULL);
			}
		//	ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
		}
	}
	//释放资源
	for(i = 0; i < maplen;i++)
	{
		if(map[i] != NULL)
		{
			free(map[i]);
			map[i] = NULL;
		}
	}

	free(map);
	map = NULL;

	return 0;
}
