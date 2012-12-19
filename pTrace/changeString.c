/*
 * @FileName: changeString.c
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
 * @Date: 2012年03月11日星期日18:27:36
 * 
 */ 
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/user.h>
#include <sys/syscall.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/reg.h>

const int LONG_SIZE = sizeof(long);
const char* TEST_STR = "JOKER TEST~~~~,";
long change = 0;


int main()
{
	pid_t child;
	
	child = fork();

	if (child == 0)
	{
		ptrace(PTRACE_TRACEME, 0, NULL, NULL);
		execl("/bin/ls", "ls", NULL);
	}
	else 
	{
		char *newStr = NULL;
		long orig_eax;
		long param[3];
		int status;
		int toggle = 0;
		int i, j;
		struct user_regs_struct regs;

		while(1)
		{
			//printf("%d", __LINE__);
			wait(&status);
			if (WIFEXITED(status))
			{
				break;
			}

			orig_eax = ptrace(PTRACE_PEEKUSER,
							child, 4 * ORIG_EAX,
							NULL);
			if (orig_eax == SYS_write)
			{
				if (toggle == 0){
				//sys call
				toggle = 1;
				param[0] = ptrace(PTRACE_PEEKUSER,
							child, 4 * EBX,
							NULL);
				param[1] = ptrace(PTRACE_PEEKUSER,
							child, 4 * ECX,
							NULL);
				param[2] = ptrace(PTRACE_PEEKUSER,
							child, 4 * EDX,
							NULL);
	
				ptrace(PTRACE_GETREGS,child, 
							NULL, &regs);

				newStr = (char*)malloc((param[2] + 1) * sizeof(char));
				char *sPtr = newStr; 

				union {
					long val;
					char chars[LONG_SIZE];
				}data;
				i = 0;
				j = param[2] / LONG_SIZE;
				//printf("\n\n%d,%d\n\n", i, j);
				while(i < j)
				{
					data.val = ptrace(PTRACE_PEEKDATA,
									child, param[1] + 4*i,
									NULL);	
					memcpy(sPtr, data.chars, LONG_SIZE);
					i ++;
					sPtr += LONG_SIZE;
				}

				j = param[2] % LONG_SIZE;
				if (j > 0)
				{
					data.val = ptrace(PTRACE_PEEKDATA,
									child, param[1] + 4*i,
									NULL);
					memcpy(sPtr, data.chars, j);
				}
				change = param[2];
				newStr[param[2]] = '\0';

//				printf("\np0: \np1:%s,\n p2:%d\n\n",
//						 newStr,param[2]);
				i = 0;
				long len = strlen(TEST_STR);
				j = len / LONG_SIZE;
				sPtr = TEST_STR;
				while (i < j)
				{
					memcpy(data.chars, sPtr, LONG_SIZE);
					ptrace(PTRACE_POKEDATA,
						child, param[1] + 4*i, data.val);
					++i;
					sPtr += LONG_SIZE;
				}
				j = len % LONG_SIZE;
				if (j > 0)
				{
					memcpy(data.chars, sPtr, j);
					ptrace(PTRACE_POKEDATA,
						child, param[1] + 4*i, data.val);
				}

					regs.edx = len;
					ptrace(PTRACE_SETREGS,
						child, NULL, &regs);
					free(newStr);
				} else {
					//end call
					toggle = 0;
					long len = strlen(TEST_STR);
					ptrace(PTRACE_GETREGS,
						child, NULL,&regs );
					regs.eax = change;
					ptrace(PTRACE_SETREGS,
						child, NULL, &regs);
				}
			}
			ptrace(PTRACE_SYSCALL, child, NULL, NULL);
		}
	}
	return 0;
}
