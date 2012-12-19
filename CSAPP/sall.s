	.file	"sall.c"
	.text
	.p2align 4,,15
.globl shift_left2_rightn
	.type	shift_left2_rightn, @function
shift_left2_rightn:
	pushl	%ebp
	movl	%esp, %ebp
	movl	8(%ebp), %eax
	movl	12(%ebp), %ecx
	popl	%ebp
	sall	$2, %eax
	sarl	%cl, %eax
	ret
	.size	shift_left2_rightn, .-shift_left2_rightn
	.ident	"GCC: (Ubuntu 4.4.3-4ubuntu5) 4.4.3"
	.section	.note.GNU-stack,"",@progbits
