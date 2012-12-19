/*
 * @FileName: exmple1.c
 * @Author: wzj
 * @Brief: 
 *   ptrace example1 
 * @History: 
 * 
 * 
 * 
 * @Date: 2011年10月26日星期三23:14:13
 * 
 */ 
#include<sys/ptrace.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/reg.h>

int main()
{
	pid_t child;
	long orig_eax;
	child = fork();
	
	if(child == 0)
	{
		//tell the kernel, child is traced
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("/bin/ls", "ls", NULL);
	}
	else {
		wait(NULL);
		//get the registor
		orig_eax = ptrace(PTRACE_PEEKUSER, 
						child, 4 * ORIG_EAX,
						NULL);
		printf("The child made a"
				"system call %ld\n", orig_eax);
		//tell child, continue:
		ptrace(PTRACE_CONT, child, NULL, NULL);
	}

	return 0;
}
