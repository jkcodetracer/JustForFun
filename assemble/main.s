	.file	"main.c"
	.section	.rodata
.LC0:
	.string	"codetracer"
	.text
.globl plus
	.type	plus, @function
plus:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	8(%ebp), %edx
	movl	12(%ebp), %eax
	movb	%dl, -36(%ebp)
	movb	%al, -40(%ebp)
	movl	$2, -8(%ebp)
	movl	$3, -12(%ebp)
	movl	$4, -16(%ebp)
	movb	$97, -1(%ebp)
	cmpb	$97, -36(%ebp)
	jne	.L2
	movl	$.LC0, -20(%ebp)
	movl	-20(%ebp), %eax
	movb	$107, (%eax)
	movl	28(%ebp), %eax
	movl	24(%ebp), %edx
	leal	(%edx,%eax), %eax
	jmp	.L3
.L2:
	movsbl	-40(%ebp),%eax
.L3:
	leave
	ret
	.size	plus, .-plus
	.section	.rodata
.LC1:
	.string	"plus:%d\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$48, %esp
	movl	$1, 44(%esp)
	movl	$14, 40(%esp)
	movl	$13, 32(%esp)
	movl	$45, 36(%esp)
	movl	40(%esp), %eax
	movl	%eax, 20(%esp)
	movl	44(%esp), %eax
	movl	%eax, 16(%esp)
	movl	32(%esp), %eax
	movl	36(%esp), %edx
	movl	%eax, 8(%esp)
	movl	%edx, 12(%esp)
	movl	$100, 4(%esp)
	movl	$97, (%esp)
	call	plus
	movl	$.LC1, %edx
	movl	%eax, 4(%esp)
	movl	%edx, (%esp)
	call	printf
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
