
a.out:     file format elf32-i386
a.out
architecture: i386, flags 0x00000112:
EXEC_P, HAS_SYMS, D_PAGED
start address 0x08048360

Program Header:
    PHDR off    0x00000034 vaddr 0x08048034 paddr 0x08048034 align 2**2
         filesz 0x00000100 memsz 0x00000100 flags r-x
  INTERP off    0x00000134 vaddr 0x08048134 paddr 0x08048134 align 2**0
         filesz 0x00000013 memsz 0x00000013 flags r--
    LOAD off    0x00000000 vaddr 0x08048000 paddr 0x08048000 align 2**12
         filesz 0x00000554 memsz 0x00000554 flags r-x
    LOAD off    0x00000f0c vaddr 0x08049f0c paddr 0x08049f0c align 2**12
         filesz 0x00000120 memsz 0x00000138 flags rw-
 DYNAMIC off    0x00000f20 vaddr 0x08049f20 paddr 0x08049f20 align 2**2
         filesz 0x000000d0 memsz 0x000000d0 flags rw-
    NOTE off    0x00000148 vaddr 0x08048148 paddr 0x08048148 align 2**2
         filesz 0x00000044 memsz 0x00000044 flags r--
   STACK off    0x00000000 vaddr 0x00000000 paddr 0x00000000 align 2**2
         filesz 0x00000000 memsz 0x00000000 flags rw-
   RELRO off    0x00000f0c vaddr 0x08049f0c paddr 0x08049f0c align 2**0
         filesz 0x000000f4 memsz 0x000000f4 flags r--

Dynamic Section:
  NEEDED               libc.so.6
  INIT                 0x080482e0
  FINI                 0x0804851c
  HASH                 0x0804818c
  GNU_HASH             0x080481b8
  STRTAB               0x08048238
  SYMTAB               0x080481d8
  STRSZ                0x00000051
  SYMENT               0x00000010
  DEBUG                0x00000000
  PLTGOT               0x08049ff4
  PLTRELSZ             0x00000020
  PLTREL               0x00000011
  JMPREL               0x080482c0
  REL                  0x080482b8
  RELSZ                0x00000008
  RELENT               0x00000008
  VERNEED              0x08048298
  VERNEEDNUM           0x00000001
  VERSYM               0x0804828a

Version References:
  required from libc.so.6:
    0x0d696910 0x00 02 GLIBC_2.0

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .interp       00000013  08048134  08048134  00000134  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  1 .note.ABI-tag 00000020  08048148  08048148  00000148  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  2 .note.gnu.build-id 00000024  08048168  08048168  00000168  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  3 .hash         0000002c  0804818c  0804818c  0000018c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  4 .gnu.hash     00000020  080481b8  080481b8  000001b8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  5 .dynsym       00000060  080481d8  080481d8  000001d8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  6 .dynstr       00000051  08048238  08048238  00000238  2**0
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  7 .gnu.version  0000000c  0804828a  0804828a  0000028a  2**1
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  8 .gnu.version_r 00000020  08048298  08048298  00000298  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
  9 .rel.dyn      00000008  080482b8  080482b8  000002b8  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 10 .rel.plt      00000020  080482c0  080482c0  000002c0  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 11 .init         00000030  080482e0  080482e0  000002e0  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 12 .plt          00000050  08048310  08048310  00000310  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 13 .text         000001bc  08048360  08048360  00000360  2**4
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 14 .fini         0000001c  0804851c  0804851c  0000051c  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
 15 .rodata       00000016  08048538  08048538  00000538  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 16 .eh_frame     00000004  08048550  08048550  00000550  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
 17 .ctors        00000008  08049f0c  08049f0c  00000f0c  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 18 .dtors        00000008  08049f14  08049f14  00000f14  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 19 .jcr          00000004  08049f1c  08049f1c  00000f1c  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 20 .dynamic      000000d0  08049f20  08049f20  00000f20  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 21 .got          00000004  08049ff0  08049ff0  00000ff0  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 22 .got.plt      0000001c  08049ff4  08049ff4  00000ff4  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 23 .data         0000001c  0804a010  0804a010  00001010  2**2
                  CONTENTS, ALLOC, LOAD, DATA
 24 .bss          00000018  0804a02c  0804a02c  0000102c  2**2
                  ALLOC
 25 .comment      00000048  00000000  00000000  0000102c  2**0
                  CONTENTS, READONLY
SYMBOL TABLE:
no symbols



Disassembly of section .interp:

08048134 <.interp>:
 8048134:	2f                   	das    
 8048135:	6c                   	insb   (%dx),%es:(%edi)
 8048136:	69 62 2f 6c 64 2d 6c 	imul   $0x6c2d646c,0x2f(%edx),%esp
 804813d:	69 6e 75 78 2e 73 6f 	imul   $0x6f732e78,0x75(%esi),%ebp
 8048144:	2e 32 00             	xor    %cs:(%eax),%al

Disassembly of section .note.ABI-tag:

08048148 <.note.ABI-tag>:
 8048148:	04 00                	add    $0x0,%al
 804814a:	00 00                	add    %al,(%eax)
 804814c:	10 00                	adc    %al,(%eax)
 804814e:	00 00                	add    %al,(%eax)
 8048150:	01 00                	add    %eax,(%eax)
 8048152:	00 00                	add    %al,(%eax)
 8048154:	47                   	inc    %edi
 8048155:	4e                   	dec    %esi
 8048156:	55                   	push   %ebp
 8048157:	00 00                	add    %al,(%eax)
 8048159:	00 00                	add    %al,(%eax)
 804815b:	00 02                	add    %al,(%edx)
 804815d:	00 00                	add    %al,(%eax)
 804815f:	00 06                	add    %al,(%esi)
 8048161:	00 00                	add    %al,(%eax)
 8048163:	00 0f                	add    %cl,(%edi)
 8048165:	00 00                	add    %al,(%eax)
 8048167:	00                   	.byte 0x0

Disassembly of section .note.gnu.build-id:

08048168 <.note.gnu.build-id>:
 8048168:	04 00                	add    $0x0,%al
 804816a:	00 00                	add    %al,(%eax)
 804816c:	14 00                	adc    $0x0,%al
 804816e:	00 00                	add    %al,(%eax)
 8048170:	03 00                	add    (%eax),%eax
 8048172:	00 00                	add    %al,(%eax)
 8048174:	47                   	inc    %edi
 8048175:	4e                   	dec    %esi
 8048176:	55                   	push   %ebp
 8048177:	00 ee                	add    %ch,%dh
 8048179:	99                   	cltd   
 804817a:	e2 40                	loop   80481bc <__gmon_start__@plt-0x164>
 804817c:	0f 91 f4             	setno  %ah
 804817f:	dd d0                	fst    %st(0)
 8048181:	c9                   	leave  
 8048182:	da 58 b8             	ficompl -0x48(%eax)
 8048185:	44                   	inc    %esp
 8048186:	4e                   	dec    %esi
 8048187:	1a 23                	sbb    (%ebx),%ah
 8048189:	f1                   	icebp  
 804818a:	4f                   	dec    %edi
 804818b:	57                   	push   %edi

Disassembly of section .hash:

0804818c <.hash>:
 804818c:	03 00                	add    (%eax),%eax
 804818e:	00 00                	add    %al,(%eax)
 8048190:	06                   	push   %es
 8048191:	00 00                	add    %al,(%eax)
 8048193:	00 01                	add    %al,(%ecx)
 8048195:	00 00                	add    %al,(%eax)
 8048197:	00 04 00             	add    %al,(%eax,%eax,1)
 804819a:	00 00                	add    %al,(%eax)
 804819c:	03 00                	add    (%eax),%eax
 804819e:	00 00                	add    %al,(%eax)
 80481a0:	00 00                	add    %al,(%eax)
 80481a2:	00 00                	add    %al,(%eax)
 80481a4:	00 00                	add    %al,(%eax)
 80481a6:	00 00                	add    %al,(%eax)
 80481a8:	00 00                	add    %al,(%eax)
 80481aa:	00 00                	add    %al,(%eax)
 80481ac:	05 00 00 00 02       	add    $0x2000000,%eax
 80481b1:	00 00                	add    %al,(%eax)
 80481b3:	00 00                	add    %al,(%eax)
 80481b5:	00 00                	add    %al,(%eax)
 80481b7:	00                   	.byte 0x0

Disassembly of section .gnu.hash:

080481b8 <.gnu.hash>:
 80481b8:	02 00                	add    (%eax),%al
 80481ba:	00 00                	add    %al,(%eax)
 80481bc:	05 00 00 00 01       	add    $0x1000000,%eax
 80481c1:	00 00                	add    %al,(%eax)
 80481c3:	00 05 00 00 00 00    	add    %al,0x0
 80481c9:	20 00                	and    %al,(%eax)
 80481cb:	20 00                	and    %al,(%eax)
 80481cd:	00 00                	add    %al,(%eax)
 80481cf:	00 05 00 00 00 ad    	add    %al,0xad000000
 80481d5:	4b                   	dec    %ebx
 80481d6:	e3 c0                	jecxz  8048198 <__gmon_start__@plt-0x188>

Disassembly of section .dynsym:

080481d8 <.dynsym>:
 80481d8:	00 00                	add    %al,(%eax)
 80481da:	00 00                	add    %al,(%eax)
 80481dc:	00 00                	add    %al,(%eax)
 80481de:	00 00                	add    %al,(%eax)
 80481e0:	00 00                	add    %al,(%eax)
 80481e2:	00 00                	add    %al,(%eax)
 80481e4:	00 00                	add    %al,(%eax)
 80481e6:	00 00                	add    %al,(%eax)
 80481e8:	01 00                	add    %eax,(%eax)
 80481ea:	00 00                	add    %al,(%eax)
 80481ec:	00 00                	add    %al,(%eax)
 80481ee:	00 00                	add    %al,(%eax)
 80481f0:	00 00                	add    %al,(%eax)
 80481f2:	00 00                	add    %al,(%eax)
 80481f4:	20 00                	and    %al,(%eax)
 80481f6:	00 00                	add    %al,(%eax)
 80481f8:	35 00 00 00 00       	xor    $0x0,%eax
 80481fd:	00 00                	add    %al,(%eax)
 80481ff:	00 00                	add    %al,(%eax)
 8048201:	00 00                	add    %al,(%eax)
 8048203:	00 12                	add    %dl,(%edx)
 8048205:	00 00                	add    %al,(%eax)
 8048207:	00 2e                	add    %ch,(%esi)
 8048209:	00 00                	add    %al,(%eax)
 804820b:	00 00                	add    %al,(%eax)
 804820d:	00 00                	add    %al,(%eax)
 804820f:	00 00                	add    %al,(%eax)
 8048211:	00 00                	add    %al,(%eax)
 8048213:	00 12                	add    %dl,(%edx)
 8048215:	00 00                	add    %al,(%eax)
 8048217:	00 29                	add    %ch,(%ecx)
 8048219:	00 00                	add    %al,(%eax)
 804821b:	00 00                	add    %al,(%eax)
 804821d:	00 00                	add    %al,(%eax)
 804821f:	00 00                	add    %al,(%eax)
 8048221:	00 00                	add    %al,(%eax)
 8048223:	00 12                	add    %dl,(%edx)
 8048225:	00 00                	add    %al,(%eax)
 8048227:	00 1a                	add    %bl,(%edx)
 8048229:	00 00                	add    %al,(%eax)
 804822b:	00 3c 85 04 08 04 00 	add    %bh,0x40804(,%eax,4)
 8048232:	00 00                	add    %al,(%eax)
 8048234:	11 00                	adc    %eax,(%eax)
 8048236:	10 00                	adc    %al,(%eax)

Disassembly of section .dynstr:

08048238 <.dynstr>:
 8048238:	00 5f 5f             	add    %bl,0x5f(%edi)
 804823b:	67 6d                	addr16 insl (%dx),%es:(%di)
 804823d:	6f                   	outsl  %ds:(%esi),(%dx)
 804823e:	6e                   	outsb  %ds:(%esi),(%dx)
 804823f:	5f                   	pop    %edi
 8048240:	73 74                	jae    80482b6 <__gmon_start__@plt-0x6a>
 8048242:	61                   	popa   
 8048243:	72 74                	jb     80482b9 <__gmon_start__@plt-0x67>
 8048245:	5f                   	pop    %edi
 8048246:	5f                   	pop    %edi
 8048247:	00 6c 69 62          	add    %ch,0x62(%ecx,%ebp,2)
 804824b:	63 2e                	arpl   %bp,(%esi)
 804824d:	73 6f                	jae    80482be <__gmon_start__@plt-0x62>
 804824f:	2e 36 00 5f 49       	add    %bl,%cs:%ss:0x49(%edi)
 8048254:	4f                   	dec    %edi
 8048255:	5f                   	pop    %edi
 8048256:	73 74                	jae    80482cc <__gmon_start__@plt-0x54>
 8048258:	64 69 6e 5f 75 73 65 	imul   $0x64657375,%fs:0x5f(%esi),%ebp
 804825f:	64 
 8048260:	00 70 75             	add    %dh,0x75(%eax)
 8048263:	74 73                	je     80482d8 <__gmon_start__@plt-0x48>
 8048265:	00 70 72             	add    %dh,0x72(%eax)
 8048268:	69 6e 74 66 00 5f 5f 	imul   $0x5f5f0066,0x74(%esi),%ebp
 804826f:	6c                   	insb   (%dx),%es:(%edi)
 8048270:	69 62 63 5f 73 74 61 	imul   $0x6174735f,0x63(%edx),%esp
 8048277:	72 74                	jb     80482ed <__gmon_start__@plt-0x33>
 8048279:	5f                   	pop    %edi
 804827a:	6d                   	insl   (%dx),%es:(%edi)
 804827b:	61                   	popa   
 804827c:	69 6e 00 47 4c 49 42 	imul   $0x42494c47,0x0(%esi),%ebp
 8048283:	43                   	inc    %ebx
 8048284:	5f                   	pop    %edi
 8048285:	32 2e                	xor    (%esi),%ch
 8048287:	30 00                	xor    %al,(%eax)

Disassembly of section .gnu.version:

0804828a <.gnu.version>:
 804828a:	00 00                	add    %al,(%eax)
 804828c:	00 00                	add    %al,(%eax)
 804828e:	02 00                	add    (%eax),%al
 8048290:	02 00                	add    (%eax),%al
 8048292:	02 00                	add    (%eax),%al
 8048294:	01 00                	add    %eax,(%eax)

Disassembly of section .gnu.version_r:

08048298 <.gnu.version_r>:
 8048298:	01 00                	add    %eax,(%eax)
 804829a:	01 00                	add    %eax,(%eax)
 804829c:	10 00                	adc    %al,(%eax)
 804829e:	00 00                	add    %al,(%eax)
 80482a0:	10 00                	adc    %al,(%eax)
 80482a2:	00 00                	add    %al,(%eax)
 80482a4:	00 00                	add    %al,(%eax)
 80482a6:	00 00                	add    %al,(%eax)
 80482a8:	10 69 69             	adc    %ch,0x69(%ecx)
 80482ab:	0d 00 00 02 00       	or     $0x20000,%eax
 80482b0:	47                   	inc    %edi
 80482b1:	00 00                	add    %al,(%eax)
 80482b3:	00 00                	add    %al,(%eax)
 80482b5:	00 00                	add    %al,(%eax)
 80482b7:	00                   	.byte 0x0

Disassembly of section .rel.dyn:

080482b8 <.rel.dyn>:
 80482b8:	f0 9f                	lock lahf 
 80482ba:	04 08                	add    $0x8,%al
 80482bc:	06                   	push   %es
 80482bd:	01 00                	add    %eax,(%eax)
 80482bf:	00                   	.byte 0x0

Disassembly of section .rel.plt:

080482c0 <.rel.plt>:
 80482c0:	00 a0 04 08 07 01    	add    %ah,0x1070804(%eax)
 80482c6:	00 00                	add    %al,(%eax)
 80482c8:	04 a0                	add    $0xa0,%al
 80482ca:	04 08                	add    $0x8,%al
 80482cc:	07                   	pop    %es
 80482cd:	02 00                	add    (%eax),%al
 80482cf:	00 08                	add    %cl,(%eax)
 80482d1:	a0 04 08 07 03       	mov    0x3070804,%al
 80482d6:	00 00                	add    %al,(%eax)
 80482d8:	0c a0                	or     $0xa0,%al
 80482da:	04 08                	add    $0x8,%al
 80482dc:	07                   	pop    %es
 80482dd:	04 00                	add    $0x0,%al
 80482df:	00                   	.byte 0x0

Disassembly of section .init:

080482e0 <.init>:
 80482e0:	55                   	push   %ebp
 80482e1:	89 e5                	mov    %esp,%ebp
 80482e3:	53                   	push   %ebx
 80482e4:	83 ec 04             	sub    $0x4,%esp
 80482e7:	e8 00 00 00 00       	call   80482ec <__gmon_start__@plt-0x34>
 80482ec:	5b                   	pop    %ebx
 80482ed:	81 c3 08 1d 00 00    	add    $0x1d08,%ebx
 80482f3:	8b 93 fc ff ff ff    	mov    -0x4(%ebx),%edx
 80482f9:	85 d2                	test   %edx,%edx
 80482fb:	74 05                	je     8048302 <__gmon_start__@plt-0x1e>
 80482fd:	e8 1e 00 00 00       	call   8048320 <__gmon_start__@plt>
 8048302:	e8 e9 00 00 00       	call   80483f0 <puts@plt+0xa0>
 8048307:	e8 e4 01 00 00       	call   80484f0 <puts@plt+0x1a0>
 804830c:	58                   	pop    %eax
 804830d:	5b                   	pop    %ebx
 804830e:	c9                   	leave  
 804830f:	c3                   	ret    

Disassembly of section .plt:

08048310 <__gmon_start__@plt-0x10>:
 8048310:	ff 35 f8 9f 04 08    	pushl  0x8049ff8
 8048316:	ff 25 fc 9f 04 08    	jmp    *0x8049ffc
 804831c:	00 00                	add    %al,(%eax)
 804831e:	00 00                	add    %al,(%eax)

08048320 <__gmon_start__@plt>:
 8048320:	ff 25 00 a0 04 08    	jmp    *0x804a000
 8048326:	68 00 00 00 00       	push   $0x0
 804832b:	e9 e0 ff ff ff       	jmp    8048310 <__gmon_start__@plt-0x10>

08048330 <__libc_start_main@plt>:
 8048330:	ff 25 04 a0 04 08    	jmp    *0x804a004
 8048336:	68 08 00 00 00       	push   $0x8
 804833b:	e9 d0 ff ff ff       	jmp    8048310 <__gmon_start__@plt-0x10>

08048340 <printf@plt>:
 8048340:	ff 25 08 a0 04 08    	jmp    *0x804a008
 8048346:	68 10 00 00 00       	push   $0x10
 804834b:	e9 c0 ff ff ff       	jmp    8048310 <__gmon_start__@plt-0x10>

08048350 <puts@plt>:
 8048350:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 8048356:	68 18 00 00 00       	push   $0x18
 804835b:	e9 b0 ff ff ff       	jmp    8048310 <__gmon_start__@plt-0x10>

Disassembly of section .text:

08048360 <.text>:
 8048360:	31 ed                	xor    %ebp,%ebp
 8048362:	5e                   	pop    %esi
 8048363:	89 e1                	mov    %esp,%ecx
 8048365:	83 e4 f0             	and    $0xfffffff0,%esp
 8048368:	50                   	push   %eax
 8048369:	54                   	push   %esp
 804836a:	52                   	push   %edx
 804836b:	68 80 84 04 08       	push   $0x8048480
 8048370:	68 90 84 04 08       	push   $0x8048490
 8048375:	51                   	push   %ecx
 8048376:	56                   	push   %esi
 8048377:	68 3a 84 04 08       	push   $0x804843a
 804837c:	e8 af ff ff ff       	call   8048330 <__libc_start_main@plt>
 8048381:	f4                   	hlt    
 8048382:	90                   	nop
 8048383:	90                   	nop
 8048384:	90                   	nop
 8048385:	90                   	nop
 8048386:	90                   	nop
 8048387:	90                   	nop
 8048388:	90                   	nop
 8048389:	90                   	nop
 804838a:	90                   	nop
 804838b:	90                   	nop
 804838c:	90                   	nop
 804838d:	90                   	nop
 804838e:	90                   	nop
 804838f:	90                   	nop
 8048390:	55                   	push   %ebp
 8048391:	89 e5                	mov    %esp,%ebp
 8048393:	53                   	push   %ebx
 8048394:	83 ec 04             	sub    $0x4,%esp
 8048397:	80 3d 2c a0 04 08 00 	cmpb   $0x0,0x804a02c
 804839e:	75 3f                	jne    80483df <puts@plt+0x8f>
 80483a0:	a1 30 a0 04 08       	mov    0x804a030,%eax
 80483a5:	bb 18 9f 04 08       	mov    $0x8049f18,%ebx
 80483aa:	81 eb 14 9f 04 08    	sub    $0x8049f14,%ebx
 80483b0:	c1 fb 02             	sar    $0x2,%ebx
 80483b3:	83 eb 01             	sub    $0x1,%ebx
 80483b6:	39 d8                	cmp    %ebx,%eax
 80483b8:	73 1e                	jae    80483d8 <puts@plt+0x88>
 80483ba:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 80483c0:	83 c0 01             	add    $0x1,%eax
 80483c3:	a3 30 a0 04 08       	mov    %eax,0x804a030
 80483c8:	ff 14 85 14 9f 04 08 	call   *0x8049f14(,%eax,4)
 80483cf:	a1 30 a0 04 08       	mov    0x804a030,%eax
 80483d4:	39 d8                	cmp    %ebx,%eax
 80483d6:	72 e8                	jb     80483c0 <puts@plt+0x70>
 80483d8:	c6 05 2c a0 04 08 01 	movb   $0x1,0x804a02c
 80483df:	83 c4 04             	add    $0x4,%esp
 80483e2:	5b                   	pop    %ebx
 80483e3:	5d                   	pop    %ebp
 80483e4:	c3                   	ret    
 80483e5:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 80483e9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi
 80483f0:	55                   	push   %ebp
 80483f1:	89 e5                	mov    %esp,%ebp
 80483f3:	83 ec 18             	sub    $0x18,%esp
 80483f6:	a1 1c 9f 04 08       	mov    0x8049f1c,%eax
 80483fb:	85 c0                	test   %eax,%eax
 80483fd:	74 12                	je     8048411 <puts@plt+0xc1>
 80483ff:	b8 00 00 00 00       	mov    $0x0,%eax
 8048404:	85 c0                	test   %eax,%eax
 8048406:	74 09                	je     8048411 <puts@plt+0xc1>
 8048408:	c7 04 24 1c 9f 04 08 	movl   $0x8049f1c,(%esp)
 804840f:	ff d0                	call   *%eax
 8048411:	c9                   	leave  
 8048412:	c3                   	ret    
 8048413:	90                   	nop
 8048414:	55                   	push   %ebp
 8048415:	89 e5                	mov    %esp,%ebp
 8048417:	83 ec 18             	sub    $0x18,%esp
 804841a:	a1 3c a0 04 08       	mov    0x804a03c,%eax
 804841f:	83 c0 01             	add    $0x1,%eax
 8048422:	a3 3c a0 04 08       	mov    %eax,0x804a03c
 8048427:	c7 04 24 40 85 04 08 	movl   $0x8048540,(%esp)
 804842e:	e8 1d ff ff ff       	call   8048350 <puts@plt>
 8048433:	b8 00 00 00 00       	mov    $0x0,%eax
 8048438:	c9                   	leave  
 8048439:	c3                   	ret    
 804843a:	55                   	push   %ebp
 804843b:	89 e5                	mov    %esp,%ebp
 804843d:	83 e4 f0             	and    $0xfffffff0,%esp
 8048440:	83 ec 20             	sub    $0x20,%esp
 8048443:	c7 44 24 18 64 00 00 	movl   $0x64,0x18(%esp)
 804844a:	00 
 804844b:	a1 40 a0 04 08       	mov    0x804a040,%eax
 8048450:	83 c0 01             	add    $0x1,%eax
 8048453:	a3 40 a0 04 08       	mov    %eax,0x804a040
 8048458:	b8 48 85 04 08       	mov    $0x8048548,%eax
 804845d:	8b 54 24 18          	mov    0x18(%esp),%edx
 8048461:	89 54 24 04          	mov    %edx,0x4(%esp)
 8048465:	89 04 24             	mov    %eax,(%esp)
 8048468:	e8 d3 fe ff ff       	call   8048340 <printf@plt>
 804846d:	b8 00 00 00 00       	mov    $0x0,%eax
 8048472:	c9                   	leave  
 8048473:	c3                   	ret    
 8048474:	90                   	nop
 8048475:	90                   	nop
 8048476:	90                   	nop
 8048477:	90                   	nop
 8048478:	90                   	nop
 8048479:	90                   	nop
 804847a:	90                   	nop
 804847b:	90                   	nop
 804847c:	90                   	nop
 804847d:	90                   	nop
 804847e:	90                   	nop
 804847f:	90                   	nop
 8048480:	55                   	push   %ebp
 8048481:	89 e5                	mov    %esp,%ebp
 8048483:	5d                   	pop    %ebp
 8048484:	c3                   	ret    
 8048485:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048489:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi
 8048490:	55                   	push   %ebp
 8048491:	89 e5                	mov    %esp,%ebp
 8048493:	57                   	push   %edi
 8048494:	56                   	push   %esi
 8048495:	53                   	push   %ebx
 8048496:	e8 4f 00 00 00       	call   80484ea <puts@plt+0x19a>
 804849b:	81 c3 59 1b 00 00    	add    $0x1b59,%ebx
 80484a1:	83 ec 1c             	sub    $0x1c,%esp
 80484a4:	e8 37 fe ff ff       	call   80482e0 <__gmon_start__@plt-0x40>
 80484a9:	8d bb 18 ff ff ff    	lea    -0xe8(%ebx),%edi
 80484af:	8d 83 18 ff ff ff    	lea    -0xe8(%ebx),%eax
 80484b5:	29 c7                	sub    %eax,%edi
 80484b7:	c1 ff 02             	sar    $0x2,%edi
 80484ba:	85 ff                	test   %edi,%edi
 80484bc:	74 24                	je     80484e2 <puts@plt+0x192>
 80484be:	31 f6                	xor    %esi,%esi
 80484c0:	8b 45 10             	mov    0x10(%ebp),%eax
 80484c3:	89 44 24 08          	mov    %eax,0x8(%esp)
 80484c7:	8b 45 0c             	mov    0xc(%ebp),%eax
 80484ca:	89 44 24 04          	mov    %eax,0x4(%esp)
 80484ce:	8b 45 08             	mov    0x8(%ebp),%eax
 80484d1:	89 04 24             	mov    %eax,(%esp)
 80484d4:	ff 94 b3 18 ff ff ff 	call   *-0xe8(%ebx,%esi,4)
 80484db:	83 c6 01             	add    $0x1,%esi
 80484de:	39 fe                	cmp    %edi,%esi
 80484e0:	72 de                	jb     80484c0 <puts@plt+0x170>
 80484e2:	83 c4 1c             	add    $0x1c,%esp
 80484e5:	5b                   	pop    %ebx
 80484e6:	5e                   	pop    %esi
 80484e7:	5f                   	pop    %edi
 80484e8:	5d                   	pop    %ebp
 80484e9:	c3                   	ret    
 80484ea:	8b 1c 24             	mov    (%esp),%ebx
 80484ed:	c3                   	ret    
 80484ee:	90                   	nop
 80484ef:	90                   	nop
 80484f0:	55                   	push   %ebp
 80484f1:	89 e5                	mov    %esp,%ebp
 80484f3:	53                   	push   %ebx
 80484f4:	83 ec 04             	sub    $0x4,%esp
 80484f7:	a1 0c 9f 04 08       	mov    0x8049f0c,%eax
 80484fc:	83 f8 ff             	cmp    $0xffffffff,%eax
 80484ff:	74 13                	je     8048514 <puts@plt+0x1c4>
 8048501:	bb 0c 9f 04 08       	mov    $0x8049f0c,%ebx
 8048506:	66 90                	xchg   %ax,%ax
 8048508:	83 eb 04             	sub    $0x4,%ebx
 804850b:	ff d0                	call   *%eax
 804850d:	8b 03                	mov    (%ebx),%eax
 804850f:	83 f8 ff             	cmp    $0xffffffff,%eax
 8048512:	75 f4                	jne    8048508 <puts@plt+0x1b8>
 8048514:	83 c4 04             	add    $0x4,%esp
 8048517:	5b                   	pop    %ebx
 8048518:	5d                   	pop    %ebp
 8048519:	c3                   	ret    
 804851a:	90                   	nop
 804851b:	90                   	nop

Disassembly of section .fini:

0804851c <.fini>:
 804851c:	55                   	push   %ebp
 804851d:	89 e5                	mov    %esp,%ebp
 804851f:	53                   	push   %ebx
 8048520:	83 ec 04             	sub    $0x4,%esp
 8048523:	e8 00 00 00 00       	call   8048528 <puts@plt+0x1d8>
 8048528:	5b                   	pop    %ebx
 8048529:	81 c3 cc 1a 00 00    	add    $0x1acc,%ebx
 804852f:	e8 5c fe ff ff       	call   8048390 <puts@plt+0x40>
 8048534:	59                   	pop    %ecx
 8048535:	5b                   	pop    %ebx
 8048536:	c9                   	leave  
 8048537:	c3                   	ret    

Disassembly of section .rodata:

08048538 <_IO_stdin_used-0x4>:
 8048538:	03 00                	add    (%eax),%eax
 804853a:	00 00                	add    %al,(%eax)

0804853c <_IO_stdin_used>:
 804853c:	01 00                	add    %eax,(%eax)
 804853e:	02 00                	add    (%eax),%al
 8048540:	68 65 6c 6c 6f       	push   $0x6f6c6c65
 8048545:	2e 2e 00 25 64 2e 2e 	add    %ah,%cs:0xa2e2e64
 804854c:	0a 
 804854d:	00                   	.byte 0x0

Disassembly of section .eh_frame:

08048550 <.eh_frame>:
 8048550:	00 00                	add    %al,(%eax)
 8048552:	00 00                	add    %al,(%eax)

Disassembly of section .ctors:

08049f0c <.ctors>:
 8049f0c:	ff                   	(bad)  
 8049f0d:	ff                   	(bad)  
 8049f0e:	ff                   	(bad)  
 8049f0f:	ff 00                	incl   (%eax)
 8049f11:	00 00                	add    %al,(%eax)
 8049f13:	00                   	.byte 0x0

Disassembly of section .dtors:

08049f14 <.dtors>:
 8049f14:	ff                   	(bad)  
 8049f15:	ff                   	(bad)  
 8049f16:	ff                   	(bad)  
 8049f17:	ff 00                	incl   (%eax)
 8049f19:	00 00                	add    %al,(%eax)
 8049f1b:	00                   	.byte 0x0

Disassembly of section .jcr:

08049f1c <.jcr>:
 8049f1c:	00 00                	add    %al,(%eax)
 8049f1e:	00 00                	add    %al,(%eax)

Disassembly of section .dynamic:

08049f20 <.dynamic>:
 8049f20:	01 00                	add    %eax,(%eax)
 8049f22:	00 00                	add    %al,(%eax)
 8049f24:	10 00                	adc    %al,(%eax)
 8049f26:	00 00                	add    %al,(%eax)
 8049f28:	0c 00                	or     $0x0,%al
 8049f2a:	00 00                	add    %al,(%eax)
 8049f2c:	e0 82                	loopne 8049eb0 <_IO_stdin_used+0x1974>
 8049f2e:	04 08                	add    $0x8,%al
 8049f30:	0d 00 00 00 1c       	or     $0x1c000000,%eax
 8049f35:	85 04 08             	test   %eax,(%eax,%ecx,1)
 8049f38:	04 00                	add    $0x0,%al
 8049f3a:	00 00                	add    %al,(%eax)
 8049f3c:	8c 81 04 08 f5 fe    	mov    %es,-0x10af7fc(%ecx)
 8049f42:	ff 6f b8             	ljmp   *-0x48(%edi)
 8049f45:	81 04 08 05 00 00 00 	addl   $0x5,(%eax,%ecx,1)
 8049f4c:	38 82 04 08 06 00    	cmp    %al,0x60804(%edx)
 8049f52:	00 00                	add    %al,(%eax)
 8049f54:	d8 81 04 08 0a 00    	fadds  0xa0804(%ecx)
 8049f5a:	00 00                	add    %al,(%eax)
 8049f5c:	51                   	push   %ecx
 8049f5d:	00 00                	add    %al,(%eax)
 8049f5f:	00 0b                	add    %cl,(%ebx)
 8049f61:	00 00                	add    %al,(%eax)
 8049f63:	00 10                	add    %dl,(%eax)
 8049f65:	00 00                	add    %al,(%eax)
 8049f67:	00 15 00 00 00 00    	add    %dl,0x0
 8049f6d:	00 00                	add    %al,(%eax)
 8049f6f:	00 03                	add    %al,(%ebx)
 8049f71:	00 00                	add    %al,(%eax)
 8049f73:	00 f4                	add    %dh,%ah
 8049f75:	9f                   	lahf   
 8049f76:	04 08                	add    $0x8,%al
 8049f78:	02 00                	add    (%eax),%al
 8049f7a:	00 00                	add    %al,(%eax)
 8049f7c:	20 00                	and    %al,(%eax)
 8049f7e:	00 00                	add    %al,(%eax)
 8049f80:	14 00                	adc    $0x0,%al
 8049f82:	00 00                	add    %al,(%eax)
 8049f84:	11 00                	adc    %eax,(%eax)
 8049f86:	00 00                	add    %al,(%eax)
 8049f88:	17                   	pop    %ss
 8049f89:	00 00                	add    %al,(%eax)
 8049f8b:	00 c0                	add    %al,%al
 8049f8d:	82                   	(bad)  
 8049f8e:	04 08                	add    $0x8,%al
 8049f90:	11 00                	adc    %eax,(%eax)
 8049f92:	00 00                	add    %al,(%eax)
 8049f94:	b8 82 04 08 12       	mov    $0x12080482,%eax
 8049f99:	00 00                	add    %al,(%eax)
 8049f9b:	00 08                	add    %cl,(%eax)
 8049f9d:	00 00                	add    %al,(%eax)
 8049f9f:	00 13                	add    %dl,(%ebx)
 8049fa1:	00 00                	add    %al,(%eax)
 8049fa3:	00 08                	add    %cl,(%eax)
 8049fa5:	00 00                	add    %al,(%eax)
 8049fa7:	00 fe                	add    %bh,%dh
 8049fa9:	ff                   	(bad)  
 8049faa:	ff 6f 98             	ljmp   *-0x68(%edi)
 8049fad:	82                   	(bad)  
 8049fae:	04 08                	add    $0x8,%al
 8049fb0:	ff                   	(bad)  
 8049fb1:	ff                   	(bad)  
 8049fb2:	ff 6f 01             	ljmp   *0x1(%edi)
 8049fb5:	00 00                	add    %al,(%eax)
 8049fb7:	00 f0                	add    %dh,%al
 8049fb9:	ff                   	(bad)  
 8049fba:	ff 6f 8a             	ljmp   *-0x76(%edi)
 8049fbd:	82                   	(bad)  
 8049fbe:	04 08                	add    $0x8,%al
 8049fc0:	00 00                	add    %al,(%eax)
 8049fc2:	00 00                	add    %al,(%eax)
 8049fc4:	00 00                	add    %al,(%eax)
 8049fc6:	00 00                	add    %al,(%eax)
 8049fc8:	00 00                	add    %al,(%eax)
 8049fca:	00 00                	add    %al,(%eax)
 8049fcc:	00 00                	add    %al,(%eax)
 8049fce:	00 00                	add    %al,(%eax)
 8049fd0:	00 00                	add    %al,(%eax)
 8049fd2:	00 00                	add    %al,(%eax)
 8049fd4:	00 00                	add    %al,(%eax)
 8049fd6:	00 00                	add    %al,(%eax)
 8049fd8:	00 00                	add    %al,(%eax)
 8049fda:	00 00                	add    %al,(%eax)
 8049fdc:	00 00                	add    %al,(%eax)
 8049fde:	00 00                	add    %al,(%eax)
 8049fe0:	00 00                	add    %al,(%eax)
 8049fe2:	00 00                	add    %al,(%eax)
 8049fe4:	00 00                	add    %al,(%eax)
 8049fe6:	00 00                	add    %al,(%eax)
 8049fe8:	00 00                	add    %al,(%eax)
 8049fea:	00 00                	add    %al,(%eax)
 8049fec:	00 00                	add    %al,(%eax)
 8049fee:	00 00                	add    %al,(%eax)

Disassembly of section .got:

08049ff0 <.got>:
 8049ff0:	00 00                	add    %al,(%eax)
 8049ff2:	00 00                	add    %al,(%eax)

Disassembly of section .got.plt:

08049ff4 <.got.plt>:
 8049ff4:	20 9f 04 08 00 00    	and    %bl,0x804(%edi)
 8049ffa:	00 00                	add    %al,(%eax)
 8049ffc:	00 00                	add    %al,(%eax)
 8049ffe:	00 00                	add    %al,(%eax)
 804a000:	26 83 04 08 36       	addl   $0x36,%es:(%eax,%ecx,1)
 804a005:	83 04 08 46          	addl   $0x46,(%eax,%ecx,1)
 804a009:	83 04 08 56          	addl   $0x56,(%eax,%ecx,1)
 804a00d:	83                   	.byte 0x83
 804a00e:	04 08                	add    $0x8,%al

Disassembly of section .data:

0804a010 <.data>:
 804a010:	00 00                	add    %al,(%eax)
 804a012:	00 00                	add    %al,(%eax)
 804a014:	00 00                	add    %al,(%eax)
 804a016:	00 00                	add    %al,(%eax)
 804a018:	2d 00 00 00 0c       	sub    $0xc000000,%eax
 804a01d:	00 00                	add    %al,(%eax)
 804a01f:	00 85 84 00 00 17    	add    %al,0x17000084(%ebp)
 804a025:	00 00                	add    %al,(%eax)
 804a027:	00 43 00             	add    %al,0x0(%ebx)
 804a02a:	00 00                	add    %al,(%eax)

Disassembly of section .bss:

0804a02c <.bss>:
 804a02c:	00 00                	add    %al,(%eax)
 804a02e:	00 00                	add    %al,(%eax)
 804a030:	00 00                	add    %al,(%eax)
 804a032:	00 00                	add    %al,(%eax)
 804a034:	00 00                	add    %al,(%eax)
 804a036:	00 00                	add    %al,(%eax)
 804a038:	00 00                	add    %al,(%eax)
 804a03a:	00 00                	add    %al,(%eax)
 804a03c:	00 00                	add    %al,(%eax)
 804a03e:	00 00                	add    %al,(%eax)
 804a040:	00 00                	add    %al,(%eax)
 804a042:	00 00                	add    %al,(%eax)

Disassembly of section .comment:

00000000 <.comment>:
   0:	47                   	inc    %edi
   1:	43                   	inc    %ebx
   2:	43                   	inc    %ebx
   3:	3a 20                	cmp    (%eax),%ah
   5:	28 55 62             	sub    %dl,0x62(%ebp)
   8:	75 6e                	jne    78 <__gmon_start__@plt-0x80482a8>
   a:	74 75                	je     81 <__gmon_start__@plt-0x804829f>
   c:	20 34 2e             	and    %dh,(%esi,%ebp,1)
   f:	34 2e                	xor    $0x2e,%al
  11:	33 2d 34 75 62 75    	xor    0x75627534,%ebp
  17:	6e                   	outsb  %ds:(%esi),(%dx)
  18:	74 75                	je     8f <__gmon_start__@plt-0x8048291>
  1a:	35 2e 31 29 20       	xor    $0x2029312e,%eax
  1f:	34 2e                	xor    $0x2e,%al
  21:	34 2e                	xor    $0x2e,%al
  23:	33 00                	xor    (%eax),%eax
  25:	47                   	inc    %edi
  26:	43                   	inc    %ebx
  27:	43                   	inc    %ebx
  28:	3a 20                	cmp    (%eax),%ah
  2a:	28 55 62             	sub    %dl,0x62(%ebp)
  2d:	75 6e                	jne    9d <__gmon_start__@plt-0x8048283>
  2f:	74 75                	je     a6 <__gmon_start__@plt-0x804827a>
  31:	20 34 2e             	and    %dh,(%esi,%ebp,1)
  34:	34 2e                	xor    $0x2e,%al
  36:	33 2d 34 75 62 75    	xor    0x75627534,%ebp
  3c:	6e                   	outsb  %ds:(%esi),(%dx)
  3d:	74 75                	je     b4 <__gmon_start__@plt-0x804826c>
  3f:	35 29 20 34 2e       	xor    $0x2e342029,%eax
  44:	34 2e                	xor    $0x2e,%al
  46:	33 00                	xor    (%eax),%eax
