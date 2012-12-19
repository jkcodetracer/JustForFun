	.file	"outline.c"
	.text
.globl plus
	.type	plus, @function
plus:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, -4(%ebp)
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	leal	(%edx,%eax), %eax
	movl	%eax, -4(%ebp)
	movl	-4(%ebp), %eax
	leave
	ret
	.size	plus, .-plus
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
