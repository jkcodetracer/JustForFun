/*
 * @FileName: StoleString.c
 * @Author: wzj
 * @Brief: 
 * 		1. reverse the input array 
 * @History: 
 *		2012.6.24 
 * 
 * 
 * @Date: 2011年10月30日星期日22:45:24
 * 
 */ 
#include<sys/ptrace.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/user.h>
#include<sys/syscall.h>
#include<sys/reg.h>

const int long_size = sizeof(long);
void reverse(char* str)
{
	int i, j;
	char temp;
	for(i = 0, j = strlen(str) - 2;
		i <= j; i++, j--)
	{
		temp = str[j];
		str[i] = str[j];
		str[j] = temp;
	}
}

void getdata(pid_t child, long addr, 
			char *str, int len) 
{
	char *laddr;
	int i, j;
	//32bit data...
	union u {
		long val;
		char chars[long_size];
	}data;

	i = 0;
	j = len / long_size;
	laddr = str;
	while(i < j)
	{
		// 沿着指针addr一直取数据，获取一个数组!!
		data.val = ptrace(PTRACE_PEEKDATA,
						child, addr + i*4, 
						NULL);
		memcpy(laddr, data.chars, long_size);
		i++;
		laddr += long_size;
	}
	// incase that the 'len' equals to 0,then ptrace will error
	j = len % long_size;
	if(j != 0)
	{
		data.val = ptrace(PTRACE_PEEKDATA,
						child, addr + i * 4,
						NULL);
		memcpy(laddr, data.chars, j);
	}
	str[len] = '\0';
}

void putdata(pid_t child, long addr, 
			char *str, int len)
{
	char *laddr;
	int i, j;
	union u{
		long val;
		char chars[long_size];
	}data;
	i = 0;
	j = len / long_size;
	laddr = str;
	while(i < j)
	{
		memcpy(data.chars, laddr, long_size);
		//what is addr?  the param's addr
		//一个数组指针，我们沿着addr这个指针，一直在放数据
		ptrace(PTRACE_POKEDATA, child,
				addr + i * 4, data.val);
		i++;
		laddr += long_size;
	}
	j = len % long_size;
	if(j != 0)
	{
		memcpy(data.chars, laddr, j);
		ptrace(PTRACE_POKEDATA, child, 
				addr + i *4, data.val);
	}
}

int main()
{
	pid_t child;
	child = fork();
	if(child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("/bin/ls", "ls", NULL);
	}
	else {
		long orig_eax;
		long params[3];
		int status;
		char *str, *laddr;
		int toggle = 0;
		while(1)
		{
			wait(&status);
			if(WIFEXITED(status))
				break;
			orig_eax = ptrace(PTRACE_PEEKUSER,
							child, 4 * ORIG_EAX,
							NULL);
			if(orig_eax == SYS_write)
			{
				if(toggle == 0)
				{
					toggle = 1;
					params[0] = ptrace(PTRACE_PEEKUSER,
									child, 4 * EBX,
									NULL);
					params[1] = ptrace(PTRACE_PEEKUSER,
									child, 4 * ECX,
									NULL);
					params[2] = ptrace(PTRACE_PEEKUSER,
									child, 4 * EDX,
									NULL);
					str = (char*)malloc((params[2]+1)
									 *sizeof(char));
					getdata(child, params[1], str, 
							params[2]);
					reverse(str);
					putdata(child, params[1], str,
							params[2]);
				}
				else {
					toggle = 0;
				}
			}
			//继续child的调用
			ptrace(PTRACE_SYSCALL, child, NULL, NULL);
		}
	}
	return 0;
}

