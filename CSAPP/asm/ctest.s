	.file	"ctest.c"
	.text
	.p2align 4,,15
.globl ctest
	.type	ctest, @function
ctest:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	%edi, 8(%esp)
	movl	8(%ebp), %edx
	movl	12(%ebp), %edi
	movl	%ebx, (%esp)
	movl	16(%ebp), %ebx
	movl	%esi, 4(%esp)
	cmpl	%edi, %edx
	setl	%al
	testl	%edx, %edx
	setg	%cl
	cmpl	%edx, %edi
	adcb	%cl, %al
	cmpl	%edx, %ebx
	setge	%cl
	movl	%ecx, %esi
	addl	%esi, %eax
	cmpl	%ebx, %edx
	movl	4(%esp), %esi
	setne	%dl
	addl	%edx, %eax
	cmpl	%edi, %ebx
	movl	(%esp), %ebx
	setg	%dl
	movl	8(%esp), %edi
	movl	%ebp, %esp
	addl	%edx, %eax
	popl	%ebp
	ret
	.size	ctest, .-ctest
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
