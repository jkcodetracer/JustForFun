	.file	"env.c"
	.section	.rodata
.LC0:
	.string	"SHELL"
.LC1:
	.string	"myenv: %s   %p\n"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	$.LC0, (%esp)
	call	getenv
	movl	%eax, 28(%esp)
	movl	$.LC1, %eax
	movl	28(%esp), %edx
	movl	%edx, 8(%esp)
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
