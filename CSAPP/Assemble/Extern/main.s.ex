	.file	"main.c"
.globl ct
	.data
	.align 4
	.type	ct, @object
	.size	ct, 4
ct:
	.long	123
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$14, -4(%ebp)
	movl	ct, %eax
	addl	-4(%ebp), %eax
	movl	%eax, ct
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
