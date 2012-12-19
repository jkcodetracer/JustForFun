void
main()
{

__asm__ __volatile__(
	"	jmp forward\n\t"
"backward:\n\t"
"		popl	%esi\n\t"
"		movl	$4, %eax\n\t"
"		movl	$2, %ebx\n\t"
"		movl	%esi, %ecx\n\t"
"		movl	$12, %edx\n\t"
"		int		$0x80\n\t"
"		int3	\n\t"	
"forward:	\n\t"
"		call 	backward	\n\t"
"		.string \"Hello World \" \n\t"
		);
		//原来是 .string "Hello World\n""
		//编译不过阿.. 必须一行一个"   \n\t"
}

