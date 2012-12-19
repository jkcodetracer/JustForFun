/*
 * @FileName: TinyHelloWorld.c
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
 * @Date: 2012年06月17日星期日22:31:57
 * 
 */ 
char *str = "Hello world!\n";

struct time{
	long a;
	long b;
};

void print()
{
	struct time sleeptime= {5,1};

	asm("movl $13, %%edx \n\t"
		"movl %0, %%ecx \n\t"
		"movl $0, %%ebx \n\t"
		"movl $4, %%eax \n\t"
		"int $0x80 \n\t"
		::"r"(str):"edx", "ecx", "ebx");
	
	asm(
		"movl $0, %%ecx \n\t"
		"movl %0,%%ebx \n\t"
		"movl $162, %%eax \n\t"
		"int $0x80 \n\t"
		::"r"(&sleeptime):"ecx", "ebx"
		);
}

void
exit()
{
	asm("movl $42, %ebx \n\t"
		"movl $1, %eax \n\t"
		"int $0x80 \n\t");
}

void
nomain()
{
	while(1)
		print();
	exit();
}


