	.file	"exchange.c"
	.text
	.p2align 4,,15
.globl exchange
	.type	exchange, @function
exchange:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	movl	12(%ebp), %ecx
	movl	(%edx), %eax
	movl	%ecx, (%edx)
	popl	%ebp
	ret
	.size	exchange, .-exchange
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
