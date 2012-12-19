	.file	"3.6.c"
	.text
	.p2align 4,,15
.globl test
	.type	test, @function
test:
	pushl	%ebp
	movl	%esp, %ebp
	movl	12(%ebp), %ecx
	movl	8(%ebp), %eax
	testl	%ecx, %ecx	;用于清零
	jle	.L2
	xorl	%edx, %edx
	.p2align 4,,7
	.p2align 3
.L3:
	addl	%edx, %eax
	addl	$1, %edx
	cmpl	%ecx, %edx
	jne	.L3
.L2:
	popl	%ebp
	ret
	.size	test, .-test
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
