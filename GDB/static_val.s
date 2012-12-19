	.file	"static_val.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"%d..\n"
	.text
	.p2align 4,,15
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	andl	$-16, %esp
	subl	$16, %esp
	movl	$100, 8(%esp)
	movl	$.LC0, 4(%esp)
	movl	$1, (%esp)
	call	__printf_chk
	xorl	%eax, %eax
	leave
	ret
	.size	main, .-main
	.section	.rodata.str1.1
.LC1:
	.string	"hello..\n"
	.text
	.p2align 4,,15
.globl foo
	.type	foo, @function
foo:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$.LC1, 4(%esp)
	movl	$1, (%esp)
	addl	$1, s_foo_uninited.2113
	call	__printf_chk
	xorl	%eax, %eax
	leave
	ret
	.size	foo, .-foo
.globl g_val_init
	.data
	.align 4
	.type	g_val_init, @object
	.size	g_val_init, 4
g_val_init:
	.long	45
	.local	s_foo_uninited.2113
	.comm	s_foo_uninited.2113,4,4
	.comm	g_val_uninit,4,4
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
