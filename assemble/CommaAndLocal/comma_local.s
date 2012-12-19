	.file	"comma_local.c"
	.section	.rodata
.LC0:
	.string	"%d"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$32, %esp
	movl	$0, 28(%esp)
	jmp	.L2
.L3:
	movl	$10, 24(%esp)
	addl	$1, 24(%esp)
	addl	$1, 28(%esp)
	movl	$.LC0, %eax
	movl	24(%esp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
.L2:
	cmpl	$4, 28(%esp)
	jle	.L3
	jmp	.L4
.L5:
	movl	$0, 20(%esp)
	addl	$1, 20(%esp)
	movl	$.LC0, %eax
	movl	20(%esp), %edx
	movl	%edx, 4(%esp)
	movl	%eax, (%esp)
	call	printf
	addl	$1, 28(%esp)
.L4:
	cmpl	$9, 28(%esp)
	jle	.L5
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
