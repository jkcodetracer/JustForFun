	.file	"cond_ext.c"
	.text
	.p2align 4,,15
.globl cond
	.type	cond, @function
cond:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	testl	%eax, %eax
	je	.L3
	testl	%edx, %edx
	jle	.L3
	addl	%edx, (%eax)
.L3:
	popl	%ebp
	ret
	.size	cond, .-cond
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
