/*
 * @FileName: bkhelloword.c
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
 * @Date: 2011年11月06日星期日21:53:57
 * 
 */ 
void main()
{
__asm__("
	jmp forward
backward:
	pop1	%esi	
	movl	$4, %eax	
	movl	$2, %ebx
	mov1	%esi, %ecx
	mov1	$12, %edx
	int		$0x80
	int3			
forward:
	call	backward
	.string \"Hello World\\n\"" 
	);
}
