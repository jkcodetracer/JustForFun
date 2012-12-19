/*
 * @FileName: SingleSteps.c
 * @Author: wzj
 * @Brief: 
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2011年10月30日星期日23:39:26
 * 
 */ 
#include<sys/ptrace.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/syscall.h>
#include<sys/user.h>
#include<sys/reg.h>

int main()
{
	pid_t child;
	const int long_size = sizeof(long);
	child = fork();
	if(child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("./dummy1", "dummy1", NULL);
	}
	else {
		int status;
		wait(&status);
		union u {
			long val;
			char chars[long_size];
		}data;
		struct user_regs_struct regs;
		int start = 0;
		long ins;
		while(1)
		{
			wait(&status);
			if(WIFEXITED(status))
				break;
			ptrace(PTRACE_GETREGS,
				child, NULL, &regs);
			if(start == 1)
			{
				ins = ptrace(PTRACE_PEEKTEXT,
							child, regs.eip,
							NULL);
				printf("EIP: %lx Instruction"
						"executed: %lx\n",
						regs.eip, ins);
			}
			if(regs.orig_eax == SYS_write){
				start = 1;
				ptrace(PTRACE_SINGLESTEP, child,
					NULL, NULL);
			}
			else
				ptrace(PTRACE_SYSCALL, child, 
					NULL, NULL);
		}
	}

	return 0;
}
