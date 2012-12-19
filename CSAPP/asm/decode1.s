	.file	"decode1.c"
	.text
	.p2align 4,,15
.globl decode1
	.type	decode1, @function
decode1:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$12, %esp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ecx
	movl	16(%ebp), %edx
	movl	%ebx, (%esp)
	movl	%esi, 4(%esp)
	movl	%edi, 8(%esp)
	movl	(%ecx), %esi
	movl	(%edx), %ebx
	movl	(%eax), %edi
	movl	%edi, (%ecx)
	movl	%esi, (%edx)
	movl	%ebx, (%eax)
	movl	(%esp), %ebx
	movl	4(%esp), %esi
	movl	8(%esp), %edi
	movl	%ebp, %esp
	popl	%ebp
	ret
	.size	decode1, .-decode1
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
