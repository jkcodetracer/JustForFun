simple:
	pushl %ebp
	movl %esp, %ebp
	movl 8(%ebp), %eax
	movl (%eax), %edx
	addl 12(%ebp), %edx
	movl %edx, (%eax)
	movl %edx, %eax
	movl %ebp, %esp
	popl %ebp
	ret
