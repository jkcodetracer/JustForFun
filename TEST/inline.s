	.file	"inline.c"
	.section	.rodata
.LC0:
	.string	"..."
	.text
.globl plus
	.type	plus, @function
plus:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	$0, -12(%ebp)
	movl	$.LC0, %eax
	movl	%eax, (%esp)
	call	printf
	movl	12(%ebp), %eax
	movl	8(%ebp), %edx
	leal	(%edx,%eax), %eax
	movl	%eax, -12(%ebp)
	movl	-12(%ebp), %eax
	leave
	ret
	.size	plus, .-plus
	.section	.rodata
.LC1:
	.string	"result = %d\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	$0, 28(%esp)
	movl	$4, 4(%esp)
	movl	$2, (%esp)
	call	plus
	movl	%eax, 28(%esp)
	movl	$.LC1, %eax
	movl	28(%esp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
