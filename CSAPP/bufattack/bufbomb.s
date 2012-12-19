	.file	"bufbomb.c"
	.text
	.p2align 4,,15
.globl getxs
	.type	getxs, @function
getxs:
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%edi
	xorl	%edi, %edi
	pushl	%esi
	pushl	%ebx
	subl	$44, %esp
	movl	8(%ebp), %eax
	movl	%eax, -28(%ebp)
.L2:
	movl	$1, %esi
	.p2align 4,,7
	.p2align 3
.L13:
	movl	stdin, %eax
	movl	%eax, (%esp)
	call	_IO_getc
	cmpl	$-1, %eax
	movl	%eax, %ebx
	je	.L8
	cmpl	$10, %eax
	je	.L8
	.p2align 4,,5
	call	__ctype_b_loc
	movl	(%eax), %eax
	testb	$16, 1(%eax,%ebx,2)
	je	.L13
	leal	-48(%ebx), %eax
	cmpl	$9, %eax
	jbe	.L5
	leal	-65(%ebx), %eax
	cmpl	$5, %eax
	ja	.L6
	leal	-55(%ebx), %eax
.L5:
	testl	%esi, %esi
	je	.L7
.L15:
	movl	%eax, %edi
	xorl	%esi, %esi
	jmp	.L13
	.p2align 4,,7
	.p2align 3
.L8:
	movl	-28(%ebp), %eax
	movb	$0, (%eax)
	movl	8(%ebp), %eax
	addl	$44, %esp
	popl	%ebx
	popl	%esi
	popl	%edi
	popl	%ebp
	ret
	.p2align 4,,7
	.p2align 3
.L6:
	testl	%esi, %esi
	leal	-87(%ebx), %eax
	jne	.L15
.L7:
	movl	%edi, %edx
	sall	$4, %edx
	leal	(%edx,%eax), %eax
	movl	-28(%ebp), %edx
	movb	%al, (%edx)
	addl	$1, %edx
	movl	%edx, -28(%ebp)
	jmp	.L2
	.size	getxs, .-getxs
	.p2align 4,,15
.globl getbuf
	.type	getbuf, @function
getbuf:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$40, %esp
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	leal	-24(%ebp), %eax
	movl	%eax, (%esp)
	call	getxs
	movl	$1, %eax
	movl	-12(%ebp), %edx
	xorl	%gs:20, %edx
	jne	.L19
	leave
	ret
.L19:
	.p2align 4,,7
	.p2align 3
	call	__stack_chk_fail
	.size	getbuf, .-getbuf
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"Type Hex string:"
.LC1:
	.string	"getbuf returned 0x%x\n"
	.text
	.p2align 4,,15
.globl test
	.type	test, @function
test:
	pushl	%ebp
	movl	%esp, %ebp
	subl	$24, %esp
	movl	$.LC0, 4(%esp)
	movl	$1, (%esp)
	call	__printf_chk
	call	getbuf
	movl	$.LC1, 4(%esp)
	movl	$1, (%esp)
	movl	%eax, 8(%esp)
	call	__printf_chk
	leave
	ret
	.size	test, .-test
	.p2align 4,,15
.globl main
	.type	main, @function
main:
	leal	4(%esp), %ecx
	andl	$-16, %esp
	pushl	-4(%ecx)
	pushl	%ebp
	movl	%esp, %ebp
	pushl	%ecx
	subl	$84, %esp
	movl	%gs:20, %eax
	movl	%eax, -12(%ebp)
	xorl	%eax, %eax
	leal	-76(%ebp), %eax
	andl	$4095, %eax
	addl	$30, %eax
	andl	$8176, %eax
	subl	%eax, %esp
	leal	15(%esp), %eax
	andl	$-16, %eax
	movl	$0, (%eax)
	call	test
	xorl	%eax, %eax
	movl	-12(%ebp), %edx
	xorl	%gs:20, %edx
	jne	.L25
	movl	-4(%ebp), %ecx
	leave
	leal	-4(%ecx), %esp
	ret
.L25:
	call	__stack_chk_fail
	.size	main, .-main
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
