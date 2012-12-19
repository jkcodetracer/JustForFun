	.file	"simple.c"
	.text
.globl simple
	.type	simple, @function
simple:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	8(%ebp), %eax
	movl	(%eax), %eax
	addl	12(%ebp), %eax
	movl	%eax, -4(%ebp)
	movl	8(%ebp), %eax
	movl	-4(%ebp), %edx
	movl	%edx, (%eax)
	movl	-4(%ebp), %eax
	leave
	ret
	.size	simple, .-simple
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
