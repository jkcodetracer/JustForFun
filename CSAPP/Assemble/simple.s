	.file	"simple.c"
	.text
	.p2align 4,,15
.globl simple
	.type	simple, @function
simple:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	addl	(%edx), %eax
	movl	%eax, (%edx)
	popl	%ebp
	ret
	.size	simple, .-simple
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
