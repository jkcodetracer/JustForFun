	.file	"commar.c"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, -4(%ebp)
	movl	$13, -8(%ebp)
	movl	$123, -12(%ebp)
	movl	-8(%ebp), %eax
	movl	-12(%ebp), %edx
	leal	(%edx,%eax), %eax
	movl	%eax, -4(%ebp)
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
