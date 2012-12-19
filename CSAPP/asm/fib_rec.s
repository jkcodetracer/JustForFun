	.file	"fib_rec.c"
	.text
	.p2align 4,,15
.globl fib_rec
	.type	fib_rec, @function
fib_rec:
	pushl	%ebp
	movl	$1, %eax
	movl	%esp, %ebp
	pushl	%esi
	xorl	%esi, %esi
	pushl	%ebx
	subl	$16, %esp
	movl	8(%ebp), %ebx
	cmpl	$2, %ebx
	jle	.L3
	.p2align 4,,7
	.p2align 3
.L6:
	leal	-2(%ebx), %eax
	subl	$1, %ebx
	movl	%eax, (%esp)
	call	fib_rec
	addl	%eax, %esi
	cmpl	$2, %ebx
	jg	.L6
	leal	1(%esi), %eax
.L3:
	addl	$16, %esp
	popl	%ebx
	popl	%esi
	popl	%ebp
	ret
	.size	fib_rec, .-fib_rec
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
