/*
 * @FileName: entry.c
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
 * @Date: 2011年11月27日星期日15:39:10
 * 
 */ 
#include "minicrt.h" 

#ifdef WIN32
#include <Windows.h>
#endif

extern int main(int argc, char* argv[]);
void exit();

//deal with error and exit
static void crt_fatal_error(const char* msg)
{
	//printf("fatal error: %s", msg);
	exit(1);
}
//before main entry ,init env && heap
void mini_crt_entry(void)
{
	int ret;
#ifdef WIN32
	int flag = 0;
	int argc = 0;
	char* argv[16]; //maxmum is 16
	char* cl = GetCommandLineA();

	//analys the command line
	argv[0] = cl;
	argc++;

	while(*cl)
	{
		if(*cl == '\"')
		{
			if(flag == 0)
				flag = 1;
			else 
				flag = 0;
		} else if(*cl == ' ' && flag == 0)
		{
			if(*(cl+1))
			{
				argv[argc] = cl +1;
				argc++;
			}
			*cl = '\0';
		}

		cl++;
	}

#else
	int argc;
	char** argv;

	char* ebp_reg = 0;
	asm("movl %%ebp, %0 \n":"=r"(ebp_reg));
	
	//acording to the offset, get the argc, argv 
	argc = *(int*)(ebp_reg + 4);
	argv = (char**) (ebp_reg + 8);

#endif
	//create a run evn
	if (!mini_crt_heap_init())
	{
		crt_fatal_error("heap initialize failed");
	}

	if (!mini_crt_io_init())
	{
		crt_fatal_error("IO initialize failed");
	}
	//call main!
	ret = main(argc, argv);
	exit(ret);
}

void exit(int exitCode)
{
	//mini_crt_call_exit_routine();
#ifdef WIN32
	ExitProcess(exitCode);
#else
	asm("movl %0, %%ebx \n\t"
		"movl $1, %%eax \n\t"
		"int $0x80		\n\t"
		"hlt 			\n\t"::"m"(exitCode));
#endif
}
