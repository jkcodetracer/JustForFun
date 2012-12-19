	.file	"comma_local.c"
	.text
.globl main
	.type	main, @function
main:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$16, %esp
	movl	$0, -4(%ebp)	#i
	jmp	.L2
.L3:
	movl	$10, -8(%ebp) 	#j1
	addl	$1, -8(%ebp)	#j1
	addl	$1, -4(%ebp)	#i
.L2:
	cmpl	$4, -4(%ebp)	#i
	jle	.L3
	jmp	.L4
.L5:
	movl	$0, -12(%ebp)
	addl	$1, -12(%ebp)	#same..
	addl	$1, -4(%ebp)
.L4:
	cmpl	$9, -4(%ebp)	# do...while 的分支预测优化~
	jle	.L5
	movl	$0, %eax
	leave
	ret
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
