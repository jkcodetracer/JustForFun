/*
 * @FileName: attacher.c
 * @Author: wzj
 * @Brief: 
 *  1.附着者，专门挂载各种程序 
 *  2.只是对进程做了hook? 
 *  3.PTRACE_ATTACH///PTRACE_DETACH 
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年06月28日星期四22:45:00
 * 
 */ 
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/user.h>
#include <stdio.h>
#include <unistd.h>

int
main(int argc, char *argv[])
{
	pid_t traced_process;
	struct user_regs_struct regs;
	long ins;

	if(argc != 2)
	{
		printf("Usage: %s <pid to be traced>", argv[0], argv[1]);
		return 1;
	}

	traced_process = atoi(argv[1]);
	//插进去
	ptrace(PTRACE_ATTACH, traced_process,
			NULL, NULL);
	wait(NULL);
	printf("MAIN OUT?\n");
	//获取寄存器的信息
	ptrace(PTRACE_GETREGS, traced_process,
			regs.eip, NULL);
	ins = ptrace(PTRACE_PEEKTEXT, traced_process,
				regs.eip, NULL);
	printf("EIP: %lx Instruction executed: %lx\n", 
			regs.eip, ins);
	while(1)
	{
		sleep(3);
	}
	//发送信号，让被attach的进程继续
	//应该还是跟踪系统调用，让被attach
	//的进程有机会释放。
	ptrace(PTRACE_DETACH, traced_process,
			NULL, NULL);
	
	return 0;
}
