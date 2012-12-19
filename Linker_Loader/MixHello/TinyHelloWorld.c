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
 * @Date: 2012年06月19日星期二22:46:23
 * 
 */ 
char* str = "Hello world\n";

void
print()
{	//使用write的系统调用， write的调用号为4，原型为int write(int filedesc, char* buffer, int size)
	//这里的系统调用，先将参数写入寄存器，之后传入write调用
	asm(
	"movl $13, %%edx \n\t"		//str的长度
	"movl %0, %%ecx \n\t"           //缓冲区，这里的％0，指的是“r”后面的字符串地址，也就是传入到这段汇编的参数。
	"movl $0, %%ebx \n\t"		//打印到标准输出， 也就是0
	"movl $4, %%eax	\n\t"		//将系统调用号传入eax。 
	"int $0x80		\n\t"	//执行中断， 调用write函数
	::"r" (str):"edx","ecx", "ebx"	//传入的参数列表， 被重命名的寄存器列表。
	);
}

void
exit()
{
	asm(
		"movl $42,%ebx \n\t "			
		"movl $1, %eax \n\t"
		"int $0x80		\n\t"
	);
}
//这里是程序的入口
void
nomain()
{
	print();	
	exit();
}
