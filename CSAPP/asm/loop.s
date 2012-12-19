	.file	"loop.c"
	.text
	.p2align 4,,15
.globl loop_while
	.type	loop_while, @function
loop_while:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	movl	8(%ebp), %edx
	pushl	%esi
	pushl	%ebx
	movl	12(%ebp), %ebx
	movl	%edx, %eax
	movl	%ebx, %edi
	movl	%ebx, %ecx
	negl	%edi
	.p2align 4,,7
	.p2align 3
.L2:
	addl	%ebx, %ecx
	addl	%edx, %eax
	movl	%ecx, %esi
	addl	%edi, %edx
	subl	%ebx, %esi
	cmpl	$255, %esi
	jle	.L2
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
.L3:
	.size	loop_while, .-loop_while
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
