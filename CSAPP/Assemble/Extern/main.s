	.file	"main.c"
.globl jk
	.data
	.align 4
	.type	jk, @object
	.size	jk, 4
jk:
	.long	123
	.align 4
	.type	mm, @object
	.size	mm, 4
mm:
	.long	12344
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
