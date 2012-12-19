/*
 * @FileName: PtraceAttach.c
 * @Author: wzj
 * @Brief: 
 *  
 *  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2011年10月31日星期一23:49:24
 * 
 */ 
#include<sys/ptrace.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<sys/user.h>		// for user_regs_struct

int main(int argc, char* argv[])
{
	pid_t traced_process;
	struct user_regs_struct regs;
	long ins;
	if(argc != 2)
	{
		printf("Usage: %s < pid %s to be traced> \n",
				argv[0], argv[1]);
		exit(1);
	}
	traced_process = atoi(argv[1]);
	ptrace(PTRACE_ATTACH, traced_process,
			NULL, NULL);
	wait(NULL);
	ptrace(PTRACE_GETREGS, traced_process,
			NULL, &regs);
	ins = ptrace(PTRACE_PEEKTEXT, traced_process, 
				regs.eip, NULL);
	printf("EIP: %lx Instruction executed: %lx\n",
			regs.eip, ins);
	ptrace(PTRACE_DETACH, traced_process,
			NULL, NULL);
	return 0;
}
