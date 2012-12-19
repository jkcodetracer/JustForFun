#include <stdio.h>
#include <netinet/in.h>
#include "Jlog.h"

#include "mono_timer.h"

int main(void)
{
        char mac[]="\x01\x02\x03\x04\x05\x06";
	unsigned int k1,k2,k3;

        printf("length:%d\n", sizeof(mac));
        k1 = htonl(*(unsigned int *)(mac+2));
        k2 = ntohl(*(unsigned int *)(mac+2));
        k3 = (*(unsigned int *)(mac+2));
        printf("k1:%x\n", k1);
        printf("k2:%x\n", k2);
        printf("k3:%x\n", k3);

	int i = 0;

	BEGIN_TIMER;
	while(i < 10000000)
	{
		i++;
	}
	END_TIMER;
	PRINT_COSTS;

	int addr = 4;
	int base = 12;

	printf("index:%d\n", (addr&(base - 1)));

	while(1)
	{
		i++;	
		WRITELOG_LIMIT("%d", i);
	}

    return 1;
}


int __libc_start_main(
			int (*main) (int, char **, char **),
			int argc, 
			char *__unbounded *__unbounded ubp_av, 
			__typedof (main)init,
			void (*fini)(void),
			void (*rtld_fini)(void),
			void * __unbounded stack_end
			)
{
	//完成环境变量的提取
	
	//检查操作系统的版本
	__pthread_initialize_minimal();
	__cxa_atexit(rtld_fini, NULL, NULL);
	__libc_init_first(argc, argv, __environ);
	__cxa_atexit(fini, NULL, NULL);
	(*init)(argc, argv, __environ);

	//...
	result = main(argc, argv, __environ);
	exit(result);
}

void exit(int status)
{
	wile(__exit_funcs != NULL)
	{
		...	
		__exit_funcs = __exit_funcs->next;
	}

	...
	_exit(status);
}

_exit:
	movl 4(%esp), %ebx
	movl $_NR_exit, %eax
	int $0x80
	hlt
