	.file	"arith.c"
	.text
	.p2align 4,,15
.globl arith
	.type	arith, @function
arith:
	pushl	%ebp
	movl	%esp, %ebp
	movl	16(%ebp), %eax
	movl	12(%ebp), %edx
	xorl	8(%ebp), %edx
	popl	%ebp
	leal	(%eax,%eax,2), %eax
	sall	$4, %eax
	andl	$65535, %edx
	imull	%edx, %eax
	ret
	.size	arith, .-arith
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
