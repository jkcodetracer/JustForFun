/*
 * @FileName: trap.c
 * @Author: wzj
 * @Brief: 
 *  1.debug 工具的基本原理，将当前执行的指令换成trap指令
 *   让人们有机会看被调试的信息了.
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年06月28日星期四23:10:05
 * 
 */ 
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/user.h>
#include <stdio.h>
#include <string.h>

const int LONG_SIZE = sizeof(long);

void
getdata(pid_t child, long addr,
		char* buffer, int buf_len)
{
	union{
		char array[LONG_SIZE];	
		long data;
	}block;

	char *laddr;
	int i = 0;
	int j = buf_len / LONG_SIZE;
	laddr = buffer;

	while(i < j)
	{
		block.data = ptrace(PTRACE_PEEKDATA, child,
						addr + i*4, NULL);	
		memcpy(laddr, block.array, LONG_SIZE);
		i++;
		laddr += LONG_SIZE;
	}

	j = buf_len % LONG_SIZE;
	if(j != 0)
	{
		block.data = ptrace(PTRACE_PEEKDATA, child,
						addr + i*4, NULL);	
		memcpy(laddr, block.array, j);
	}

	buffer[buf_len] = ' ';
}

void
putdata(pid_t child, long addr,
		char *str, int len)
{
	union {
		char array[LONG_SIZE];	
		long data;
	}b;

	char* laddr = str;
	int i = 0;
	int j = len / LONG_SIZE;
	
	while(i < j)
	{
		memcpy(b.array, laddr, LONG_SIZE);
		//回溯堆栈
		ptrace(PTRACE_POKEDATA, child,
				addr + i*4, b.data);
		i++;
		laddr += LONG_SIZE;
	}

	j = len % LONG_SIZE;
	if(j > 0)
	{
		memcpy(b.array, laddr, j);
		ptrace(PTRACE_POKEDATA, child,
				addr + i*4, b.data);
	}
}

int
main(int argc, char* argv[])
{
	pid_t traced_process;
	struct user_regs_struct regs, newregs;
	long ins;
	/* int 0x80, int 3, 直接扔二进制代码进去...*/
	//char code[] = {0xcd, 0x80, 0xcc, 0};
	char code[] = { 
			"\xeb\x15\x5e\xb8\x04\x00\x00\x00"
			"\xbb\x02\x00\x00\x00\x89\xf1\xba"
			"\x0c\x00\x00\x00\xcd\x80\xcc\xe8"
			"\xe6\xff\xff\xff\x48\x65\x6c\x6c"
			"\x6f\x20\x57\x6f\x72\x6c\x64\x20\x00"
			};
	char backup[41];
	
	if(argc != 2) {
		printf("U");
		return 1;
	}

	traced_process = atoi(argv[1]);
	ptrace(PTRACE_ATTACH, traced_process,
			NULL, NULL);
	//是在等待stop信号? 这个不是等待子进程退出的吗?
	wait(NULL);
	ptrace(PTRACE_GETREGS, traced_process,
			NULL, regs);
	printf("backup..%d\n", traced_process);
	//备份掉下一条指令的前三个字节	
	getdata(traced_process, regs.eip, backup, 41);
	//偷换下一条指令	
	putdata(traced_process, regs.eip, code, 41);
	printf("sleal over\n");
	//继续attach进程
	ptrace(PTRACE_CONT, traced_process, NULL, NULL);
	wait(NULL); //等待陷入

	printf("The process stopped, putting back"
			"the original instrctions");
//	getchar();
	putdata(traced_process, regs.eip, backup, 41);
	//还原现场	
	ptrace(PTRACE_SETREGS, traced_process,
			NULL, &regs);
	ptrace(PTRACE_DETACH, traced_process,
			NULL, NULL);	
	return 0;
}
