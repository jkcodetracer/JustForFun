	org 0100h	;org 07c00h    	将程序加载到7c00处
	mov ax, cs
	mov ds, ax
	mov es, ax
	call DispStr	;调用显示字符串的例程
	jmp $			;无限循环 $为当前位置编译后的地址
					;$$表示一个section的开始处被汇编后的地址。
		
DispStr:
	mov ax, BootMessage
	mov bp, ax		;es:bp=串地址
	mov cx, 16		;cx = 串长度
	mov ax, 01301h	;ah=13, al=01h
	mov bx, 000ch	;页号为0(bh=0) 黑地红字bl＝0c 
	mov dl, 0
	int 10h			;10h号中断
	ret
BootMessage: db 'Hello, OS world!'
times 510-($-$$) db 0	;填充字节，到512
						;$-$$ 本行到程序开始的地方
						; 510 + 0xaa55占用的2b正好是512

dw 0xaa55			;结束标志


