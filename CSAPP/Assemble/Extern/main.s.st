	.file	"main.c"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$14, -4(%ebp)
	movl	ct.1702, %eax
	addl	-4(%ebp), %eax
	movl	%eax, ct.1702
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.local	ct.1702
	.comm	ct.1702,4,4
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
