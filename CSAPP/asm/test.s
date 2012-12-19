	.file	"test.c"
	.text
	.p2align 4,,15
.globl test
	.type	test, @function
test:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	movl	12(%ebp), %edx
	subl	$100, %edx
	cmpl	$33, %edx
	ja	.L3
	movl	CSWTCH.1(,%edx,4), %eax
.L3:
	popl	%ebp
	ret
	.size	test, .-test
	.section	.rodata
	.align 32
	.type	CSWTCH.1, @object
	.size	CSWTCH.1, 136
CSWTCH.1:
	.long	10
	.long	100
	.long	124
	.long	12455
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	0
	.long	12
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
