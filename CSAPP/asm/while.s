	.file	"while.c"
	.text
	.p2align 4,,15
.globl loop
	.type	loop, @function
loop:
	pushl	%ebp
	xorl	%eax, %eax
	movl	%esp, %ebp
	movl	16(%ebp), %edx
	pushl	%edi
	movl	8(%ebp), %ecx
	pushl	%esi
	pushl	%ebx
	testl	%edx, %edx
	jle	.L3
	movl	12(%ebp), %esi
	movl	%ecx, %eax
	movl	%ecx, %ebx
	notl	%eax
	negl	%ebx
	leal	(%eax,%edx), %edx
	xorl	%eax, %eax
	imull	%ecx, %esi
	.p2align 4,,7
	.p2align 3
.L4:
	addl	%ebx, %edx
	addl	%esi, %eax
	movl	%edx, %edi
	addl	%ecx, %edi
	jns	.L4
.L3:
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.size	loop, .-loop
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
