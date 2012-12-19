/*
 * @FileName: PtraceGetRegs.c
 * @Author: wzj
 * @Brief: 
 *  
  struct user_regs_struct {
       	long ebx, ecx, edx, esi, edi, ebp, eax;
		unsigned short ds, __ds, es, __es;
		unsigned short fs, __fs, gs, __gs;
		long orig_eax, eip;
		unsigned short cs, __cs;
		long eflags, esp;
		unsigned short ss, __ss;
		};
 * use this struct to get the child's regs info.
 * @History: 
 * 
 * 
 * 
 * @Date: 2011年10月27日星期四23:46:10
 * 
 */ 
#include<sys/ptrace.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<sys/reg.h>
#include<sys/syscall.h> //系统调用的别名
#include<unistd.h>
#include<sys/user.h>

int main()
{
	pid_t child;
	long orig_eax, eax;
	long params[3];
	int status;
	int insyscall = 0;
	struct user_regs_struct regs;

	child = fork();
	if(child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("/bin/ls", "ls", NULL);
	}
	else {
		while(1)
		{
		//每次系统调用后，都会发送信号告知parent
			wait(&status);
			if(WIFEXITED(status))
				break;
			orig_eax = ptrace(PTRACE_PEEKUSER,
							child, 4 * ORIG_EAX,
							NULL);
			if(orig_eax == SYS_write)
			{
				if(insyscall == 0)
				{
					insyscall = 1;
					ptrace(PTRACE_GETREGS, child,
							NULL, &regs);
					printf("Write called with "
							"%ld, %ld, %ld\n",
							regs.ebx, regs.ecx,
							regs.edx);
				}
				else{
					eax = ptrace(PTRACE_PEEKUSER,
								child, 4 * EAX,
								NULL);
					printf("Write returned"
							"with %ld\n", eax);
					insyscall = 0;
				}
			}
			ptrace(PTRACE_SYSCALL, child,
					NULL, NULL);
		}
	}
	return 0;
}
