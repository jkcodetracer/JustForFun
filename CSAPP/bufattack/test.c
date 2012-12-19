
a.out:     file format elf32-i386


Disassembly of section .init:

08048328 <_init>:
 8048328:	55                   	push   %ebp
 8048329:	89 e5                	mov    %esp,%ebp
 804832b:	53                   	push   %ebx
 804832c:	83 ec 04             	sub    $0x4,%esp
 804832f:	e8 00 00 00 00       	call   8048334 <_init+0xc>
 8048334:	5b                   	pop    %ebx
 8048335:	81 c3 c0 1c 00 00    	add    $0x1cc0,%ebx
 804833b:	8b 93 fc ff ff ff    	mov    -0x4(%ebx),%edx
 8048341:	85 d2                	test   %edx,%edx
 8048343:	74 05                	je     804834a <_init+0x22>
 8048345:	e8 2e 00 00 00       	call   8048378 <__gmon_start__@plt>
 804834a:	e8 01 01 00 00       	call   8048450 <frame_dummy>
 804834f:	e8 0c 03 00 00       	call   8048660 <__do_global_ctors_aux>
 8048354:	58                   	pop    %eax
 8048355:	5b                   	pop    %ebx
 8048356:	c9                   	leave  
 8048357:	c3                   	ret    

Disassembly of section .plt:

08048358 <getchar@plt-0x10>:
 8048358:	ff 35 f8 9f 04 08    	pushl  0x8049ff8
 804835e:	ff 25 fc 9f 04 08    	jmp    *0x8049ffc
 8048364:	00 00                	add    %al,(%eax)
	...

08048368 <getchar@plt>:
 8048368:	ff 25 00 a0 04 08    	jmp    *0x804a000
 804836e:	68 00 00 00 00       	push   $0x0
 8048373:	e9 e0 ff ff ff       	jmp    8048358 <_init+0x30>

08048378 <__gmon_start__@plt>:
 8048378:	ff 25 04 a0 04 08    	jmp    *0x804a004
 804837e:	68 08 00 00 00       	push   $0x8
 8048383:	e9 d0 ff ff ff       	jmp    8048358 <_init+0x30>

08048388 <__libc_start_main@plt>:
 8048388:	ff 25 08 a0 04 08    	jmp    *0x804a008
 804838e:	68 10 00 00 00       	push   $0x10
 8048393:	e9 c0 ff ff ff       	jmp    8048358 <_init+0x30>

08048398 <__ctype_b_loc@plt>:
 8048398:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 804839e:	68 18 00 00 00       	push   $0x18
 80483a3:	e9 b0 ff ff ff       	jmp    8048358 <_init+0x30>

080483a8 <printf@plt>:
 80483a8:	ff 25 10 a0 04 08    	jmp    *0x804a010
 80483ae:	68 20 00 00 00       	push   $0x20
 80483b3:	e9 a0 ff ff ff       	jmp    8048358 <_init+0x30>

Disassembly of section .text:

080483c0 <_start>:
 80483c0:	31 ed                	xor    %ebp,%ebp
 80483c2:	5e                   	pop    %esi
 80483c3:	89 e1                	mov    %esp,%ecx
 80483c5:	83 e4 f0             	and    $0xfffffff0,%esp
 80483c8:	50                   	push   %eax
 80483c9:	54                   	push   %esp
 80483ca:	52                   	push   %edx
 80483cb:	68 f0 85 04 08       	push   $0x80485f0
 80483d0:	68 00 86 04 08       	push   $0x8048600
 80483d5:	51                   	push   %ecx
 80483d6:	56                   	push   %esi
 80483d7:	68 8c 85 04 08       	push   $0x804858c
 80483dc:	e8 a7 ff ff ff       	call   8048388 <__libc_start_main@plt>
 80483e1:	f4                   	hlt    
 80483e2:	90                   	nop
 80483e3:	90                   	nop
 80483e4:	90                   	nop
 80483e5:	90                   	nop
 80483e6:	90                   	nop
 80483e7:	90                   	nop
 80483e8:	90                   	nop
 80483e9:	90                   	nop
 80483ea:	90                   	nop
 80483eb:	90                   	nop
 80483ec:	90                   	nop
 80483ed:	90                   	nop
 80483ee:	90                   	nop
 80483ef:	90                   	nop

080483f0 <__do_global_dtors_aux>:
 80483f0:	55                   	push   %ebp
 80483f1:	89 e5                	mov    %esp,%ebp
 80483f3:	53                   	push   %ebx
 80483f4:	83 ec 04             	sub    $0x4,%esp
 80483f7:	80 3d 1c a0 04 08 00 	cmpb   $0x0,0x804a01c
 80483fe:	75 3f                	jne    804843f <__do_global_dtors_aux+0x4f>
 8048400:	a1 20 a0 04 08       	mov    0x804a020,%eax
 8048405:	bb 18 9f 04 08       	mov    $0x8049f18,%ebx
 804840a:	81 eb 14 9f 04 08    	sub    $0x8049f14,%ebx
 8048410:	c1 fb 02             	sar    $0x2,%ebx
 8048413:	83 eb 01             	sub    $0x1,%ebx
 8048416:	39 d8                	cmp    %ebx,%eax
 8048418:	73 1e                	jae    8048438 <__do_global_dtors_aux+0x48>
 804841a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8048420:	83 c0 01             	add    $0x1,%eax
 8048423:	a3 20 a0 04 08       	mov    %eax,0x804a020
 8048428:	ff 14 85 14 9f 04 08 	call   *0x8049f14(,%eax,4)
 804842f:	a1 20 a0 04 08       	mov    0x804a020,%eax
 8048434:	39 d8                	cmp    %ebx,%eax
 8048436:	72 e8                	jb     8048420 <__do_global_dtors_aux+0x30>
 8048438:	c6 05 1c a0 04 08 01 	movb   $0x1,0x804a01c
 804843f:	83 c4 04             	add    $0x4,%esp
 8048442:	5b                   	pop    %ebx
 8048443:	5d                   	pop    %ebp
 8048444:	c3                   	ret    
 8048445:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048449:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048450 <frame_dummy>:
 8048450:	55                   	push   %ebp
 8048451:	89 e5                	mov    %esp,%ebp
 8048453:	83 ec 18             	sub    $0x18,%esp
 8048456:	a1 1c 9f 04 08       	mov    0x8049f1c,%eax
 804845b:	85 c0                	test   %eax,%eax
 804845d:	74 12                	je     8048471 <frame_dummy+0x21>
 804845f:	b8 00 00 00 00       	mov    $0x0,%eax
 8048464:	85 c0                	test   %eax,%eax
 8048466:	74 09                	je     8048471 <frame_dummy+0x21>
 8048468:	c7 04 24 1c 9f 04 08 	movl   $0x8049f1c,(%esp)
 804846f:	ff d0                	call   *%eax
 8048471:	c9                   	leave  
 8048472:	c3                   	ret    
 8048473:	90                   	nop

08048474 <getxs>:
 8048474:	55                   	push   %ebp
 8048475:	89 e5                	mov    %esp,%ebp
 8048477:	83 ec 28             	sub    $0x28,%esp
 804847a:	c7 45 e8 01 00 00 00 	movl   $0x1,-0x18(%ebp)
 8048481:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
 8048488:	8b 45 08             	mov    0x8(%ebp),%eax
 804848b:	89 45 f0             	mov    %eax,-0x10(%ebp)
 804848e:	e9 89 00 00 00       	jmp    804851c <getxs+0xa8>
 8048493:	e8 00 ff ff ff       	call   8048398 <__ctype_b_loc@plt>
 8048498:	8b 00                	mov    (%eax),%eax
 804849a:	8b 55 e4             	mov    -0x1c(%ebp),%edx
 804849d:	01 d2                	add    %edx,%edx
 804849f:	01 d0                	add    %edx,%eax
 80484a1:	0f b7 00             	movzwl (%eax),%eax
 80484a4:	0f b7 c0             	movzwl %ax,%eax
 80484a7:	25 00 10 00 00       	and    $0x1000,%eax
 80484ac:	85 c0                	test   %eax,%eax
 80484ae:	74 6c                	je     804851c <getxs+0xa8>
 80484b0:	83 7d e4 2f          	cmpl   $0x2f,-0x1c(%ebp)
 80484b4:	7e 11                	jle    80484c7 <getxs+0x53>
 80484b6:	83 7d e4 39          	cmpl   $0x39,-0x1c(%ebp)
 80484ba:	7f 0b                	jg     80484c7 <getxs+0x53>
 80484bc:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 80484bf:	83 e8 30             	sub    $0x30,%eax
 80484c2:	89 45 f4             	mov    %eax,-0xc(%ebp)
 80484c5:	eb 20                	jmp    80484e7 <getxs+0x73>
 80484c7:	83 7d e4 40          	cmpl   $0x40,-0x1c(%ebp)
 80484cb:	7e 11                	jle    80484de <getxs+0x6a>
 80484cd:	83 7d e4 46          	cmpl   $0x46,-0x1c(%ebp)
 80484d1:	7f 0b                	jg     80484de <getxs+0x6a>
 80484d3:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 80484d6:	83 e8 37             	sub    $0x37,%eax
 80484d9:	89 45 f4             	mov    %eax,-0xc(%ebp)
 80484dc:	eb 09                	jmp    80484e7 <getxs+0x73>
 80484de:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 80484e1:	83 e8 57             	sub    $0x57,%eax
 80484e4:	89 45 f4             	mov    %eax,-0xc(%ebp)
 80484e7:	83 7d e8 00          	cmpl   $0x0,-0x18(%ebp)
 80484eb:	74 0f                	je     80484fc <getxs+0x88>
 80484ed:	8b 45 f4             	mov    -0xc(%ebp),%eax
 80484f0:	89 45 ec             	mov    %eax,-0x14(%ebp)
 80484f3:	c7 45 e8 00 00 00 00 	movl   $0x0,-0x18(%ebp)
 80484fa:	eb 20                	jmp    804851c <getxs+0xa8>
 80484fc:	8b 45 ec             	mov    -0x14(%ebp),%eax
 80484ff:	89 c2                	mov    %eax,%edx
 8048501:	c1 e2 04             	shl    $0x4,%edx
 8048504:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8048507:	8d 04 02             	lea    (%edx,%eax,1),%eax
 804850a:	89 c2                	mov    %eax,%edx
 804850c:	8b 45 f0             	mov    -0x10(%ebp),%eax
 804850f:	88 10                	mov    %dl,(%eax)
 8048511:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
 8048515:	c7 45 e8 01 00 00 00 	movl   $0x1,-0x18(%ebp)
 804851c:	e8 47 fe ff ff       	call   8048368 <getchar@plt>
 8048521:	89 45 e4             	mov    %eax,-0x1c(%ebp)
 8048524:	83 7d e4 ff          	cmpl   $0xffffffff,-0x1c(%ebp)
 8048528:	74 0a                	je     8048534 <getxs+0xc0>
 804852a:	83 7d e4 0a          	cmpl   $0xa,-0x1c(%ebp)
 804852e:	0f 85 5f ff ff ff    	jne    8048493 <getxs+0x1f>
 8048534:	8b 45 f0             	mov    -0x10(%ebp),%eax
 8048537:	c6 00 00             	movb   $0x0,(%eax)
 804853a:	83 45 f0 01          	addl   $0x1,-0x10(%ebp)
 804853e:	8b 45 08             	mov    0x8(%ebp),%eax
 8048541:	c9                   	leave  
 8048542:	c3                   	ret    

08048543 <getbuf>:
 8048543:	55                   	push   %ebp
 8048544:	89 e5                	mov    %esp,%ebp
 8048546:	83 ec 28             	sub    $0x28,%esp
 8048549:	8d 45 ec             	lea    -0x14(%ebp),%eax
 804854c:	89 04 24             	mov    %eax,(%esp)
 804854f:	e8 20 ff ff ff       	call   8048474 <getxs>
 8048554:	b8 01 00 00 00       	mov    $0x1,%eax
 8048559:	c9                   	leave  
 804855a:	c3                   	ret    

0804855b <test>:
 804855b:	55                   	push   %ebp
 804855c:	89 e5                	mov    %esp,%ebp
 804855e:	83 ec 28             	sub    $0x28,%esp
 8048561:	b8 b0 86 04 08       	mov    $0x80486b0,%eax
 8048566:	89 04 24             	mov    %eax,(%esp)
 8048569:	e8 3a fe ff ff       	call   80483a8 <printf@plt>
 804856e:	e8 d0 ff ff ff       	call   8048543 <getbuf>
 8048573:	89 45 f4             	mov    %eax,-0xc(%ebp)
 8048576:	b8 c1 86 04 08       	mov    $0x80486c1,%eax
 804857b:	8b 55 f4             	mov    -0xc(%ebp),%edx
 804857e:	89 54 24 04          	mov    %edx,0x4(%esp)
 8048582:	89 04 24             	mov    %eax,(%esp)
 8048585:	e8 1e fe ff ff       	call   80483a8 <printf@plt>
 804858a:	c9                   	leave  
 804858b:	c3                   	ret    

0804858c <main>:
 804858c:	8d 4c 24 04          	lea    0x4(%esp),%ecx
 8048590:	83 e4 f0             	and    $0xfffffff0,%esp
 8048593:	ff 71 fc             	pushl  -0x4(%ecx)
 8048596:	55                   	push   %ebp
 8048597:	89 e5                	mov    %esp,%ebp
 8048599:	51                   	push   %ecx
 804859a:	83 ec 54             	sub    $0x54,%esp
 804859d:	8d 45 b0             	lea    -0x50(%ebp),%eax
 80485a0:	25 ff 0f 00 00       	and    $0xfff,%eax
 80485a5:	89 45 f0             	mov    %eax,-0x10(%ebp)
 80485a8:	8b 45 f0             	mov    -0x10(%ebp),%eax
 80485ab:	83 c0 0f             	add    $0xf,%eax
 80485ae:	83 c0 0f             	add    $0xf,%eax
 80485b1:	c1 e8 04             	shr    $0x4,%eax
 80485b4:	c1 e0 04             	shl    $0x4,%eax
 80485b7:	29 c4                	sub    %eax,%esp
 80485b9:	89 e0                	mov    %esp,%eax
 80485bb:	83 c0 0f             	add    $0xf,%eax
 80485be:	c1 e8 04             	shr    $0x4,%eax
 80485c1:	c1 e0 04             	shl    $0x4,%eax
 80485c4:	89 45 f4             	mov    %eax,-0xc(%ebp)
 80485c7:	8b 45 f4             	mov    -0xc(%ebp),%eax
 80485ca:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
 80485d0:	e8 86 ff ff ff       	call   804855b <test>
 80485d5:	b8 00 00 00 00       	mov    $0x0,%eax
 80485da:	8b 4d fc             	mov    -0x4(%ebp),%ecx
 80485dd:	c9                   	leave  
 80485de:	8d 61 fc             	lea    -0x4(%ecx),%esp
 80485e1:	c3                   	ret    
 80485e2:	90                   	nop
 80485e3:	90                   	nop
 80485e4:	90                   	nop
 80485e5:	90                   	nop
 80485e6:	90                   	nop
 80485e7:	90                   	nop
 80485e8:	90                   	nop
 80485e9:	90                   	nop
 80485ea:	90                   	nop
 80485eb:	90                   	nop
 80485ec:	90                   	nop
 80485ed:	90                   	nop
 80485ee:	90                   	nop
 80485ef:	90                   	nop

080485f0 <__libc_csu_fini>:
 80485f0:	55                   	push   %ebp
 80485f1:	89 e5                	mov    %esp,%ebp
 80485f3:	5d                   	pop    %ebp
 80485f4:	c3                   	ret    
 80485f5:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 80485f9:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048600 <__libc_csu_init>:
 8048600:	55                   	push   %ebp
 8048601:	89 e5                	mov    %esp,%ebp
 8048603:	57                   	push   %edi
 8048604:	56                   	push   %esi
 8048605:	53                   	push   %ebx
 8048606:	e8 4f 00 00 00       	call   804865a <__i686.get_pc_thunk.bx>
 804860b:	81 c3 e9 19 00 00    	add    $0x19e9,%ebx
 8048611:	83 ec 1c             	sub    $0x1c,%esp
 8048614:	e8 0f fd ff ff       	call   8048328 <_init>
 8048619:	8d bb 18 ff ff ff    	lea    -0xe8(%ebx),%edi
 804861f:	8d 83 18 ff ff ff    	lea    -0xe8(%ebx),%eax
 8048625:	29 c7                	sub    %eax,%edi
 8048627:	c1 ff 02             	sar    $0x2,%edi
 804862a:	85 ff                	test   %edi,%edi
 804862c:	74 24                	je     8048652 <__libc_csu_init+0x52>
 804862e:	31 f6                	xor    %esi,%esi
 8048630:	8b 45 10             	mov    0x10(%ebp),%eax
 8048633:	89 44 24 08          	mov    %eax,0x8(%esp)
 8048637:	8b 45 0c             	mov    0xc(%ebp),%eax
 804863a:	89 44 24 04          	mov    %eax,0x4(%esp)
 804863e:	8b 45 08             	mov    0x8(%ebp),%eax
 8048641:	89 04 24             	mov    %eax,(%esp)
 8048644:	ff 94 b3 18 ff ff ff 	call   *-0xe8(%ebx,%esi,4)
 804864b:	83 c6 01             	add    $0x1,%esi
 804864e:	39 fe                	cmp    %edi,%esi
 8048650:	72 de                	jb     8048630 <__libc_csu_init+0x30>
 8048652:	83 c4 1c             	add    $0x1c,%esp
 8048655:	5b                   	pop    %ebx
 8048656:	5e                   	pop    %esi
 8048657:	5f                   	pop    %edi
 8048658:	5d                   	pop    %ebp
 8048659:	c3                   	ret    

0804865a <__i686.get_pc_thunk.bx>:
 804865a:	8b 1c 24             	mov    (%esp),%ebx
 804865d:	c3                   	ret    
 804865e:	90                   	nop
 804865f:	90                   	nop

08048660 <__do_global_ctors_aux>:
 8048660:	55                   	push   %ebp
 8048661:	89 e5                	mov    %esp,%ebp
 8048663:	53                   	push   %ebx
 8048664:	83 ec 04             	sub    $0x4,%esp
 8048667:	a1 0c 9f 04 08       	mov    0x8049f0c,%eax
 804866c:	83 f8 ff             	cmp    $0xffffffff,%eax
 804866f:	74 13                	je     8048684 <__do_global_ctors_aux+0x24>
 8048671:	bb 0c 9f 04 08       	mov    $0x8049f0c,%ebx
 8048676:	66 90                	xchg   %ax,%ax
 8048678:	83 eb 04             	sub    $0x4,%ebx
 804867b:	ff d0                	call   *%eax
 804867d:	8b 03                	mov    (%ebx),%eax
 804867f:	83 f8 ff             	cmp    $0xffffffff,%eax
 8048682:	75 f4                	jne    8048678 <__do_global_ctors_aux+0x18>
 8048684:	83 c4 04             	add    $0x4,%esp
 8048687:	5b                   	pop    %ebx
 8048688:	5d                   	pop    %ebp
 8048689:	c3                   	ret    
 804868a:	90                   	nop
 804868b:	90                   	nop

Disassembly of section .fini:

0804868c <_fini>:
 804868c:	55                   	push   %ebp
 804868d:	89 e5                	mov    %esp,%ebp
 804868f:	53                   	push   %ebx
 8048690:	83 ec 04             	sub    $0x4,%esp
 8048693:	e8 00 00 00 00       	call   8048698 <_fini+0xc>
 8048698:	5b                   	pop    %ebx
 8048699:	81 c3 5c 19 00 00    	add    $0x195c,%ebx
 804869f:	e8 4c fd ff ff       	call   80483f0 <__do_global_dtors_aux>
 80486a4:	59                   	pop    %ecx
 80486a5:	5b                   	pop    %ebx
 80486a6:	c9                   	leave  
 80486a7:	c3                   	ret    
