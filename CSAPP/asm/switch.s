	.file	"switch.c"
	.text
	.p2align 4,,15
.globl switch2
	.type	switch2, @function
switch2:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	movl	8(%ebp), %edx
	cmpl	$4, %edx
	ja	.L3
	movl	CSWTCH.1(,%edx,4), %eax
.L3:
	popl	%ebp
	ret
	.size	switch2, .-switch2
	.section	.rodata
	.align 4
	.type	CSWTCH.1, @object
	.size	CSWTCH.1, 20
CSWTCH.1:
	.long	1
	.long	0
	.long	2
	.long	3
	.long	4
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
