	.file	"code.c"
	.text
	.p2align 4,,15
.globl sum
	.type	sum, @function
sum:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %eax
	addl	8(%ebp), %eax
	addl	%eax, accum
	popl	%ebp
	ret
	.size	sum, .-sum
.globl accum
	.bss
	.align 4
	.type	accum, @object
	.size	accum, 4
accum:
	.zero	4
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
