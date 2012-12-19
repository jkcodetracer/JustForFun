	.file	"rSum.c"
	.text
	.p2align 4,,15
.globl rSum
	.type	rSum, @function
rSum:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	pushl	%ebx
	movl	8(%ebp), %ecx
	testl	%edx, %edx
	jle	.L3
	.p2align 4,,7
	.p2align 3
.L6:
	movl	(%ecx), %ebx
	addl	$4, %ecx
	addl	%ebx, %eax
	subl	$1, %edx
	jne	.L6
.L3:
	popl	%ebx
	popl	%ebp
	ret
	.size	rSum, .-rSum
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
