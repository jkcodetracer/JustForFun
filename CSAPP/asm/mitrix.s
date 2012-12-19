	.file	"mitrix.c"
	.text
	.p2align 4,,15
.globl fix_set_diag
	.type	fix_set_diag, @function
fix_set_diag:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ecx
	leal	1156(%eax), %edx
	.p2align 4,,7
	.p2align 3
.L2:
	movl	%ecx, (%eax)
	addl	$68, %eax
	cmpl	%edx, %eax
	jne	.L2
	popl	%ebp
	ret
	.size	fix_set_diag, .-fix_set_diag
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
