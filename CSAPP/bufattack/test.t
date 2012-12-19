
a.out:     file format elf32-i386


Disassembly of section .init:

08048370 <_init>:
 8048370:	55                   	push   %ebp
 8048371:	89 e5                	mov    %esp,%ebp
 8048373:	53                   	push   %ebx
 8048374:	83 ec 04             	sub    $0x4,%esp
 8048377:	e8 00 00 00 00       	call   804837c <_init+0xc>
 804837c:	5b                   	pop    %ebx
 804837d:	81 c3 78 1c 00 00    	add    $0x1c78,%ebx
 8048383:	8b 93 fc ff ff ff    	mov    -0x4(%ebx),%edx
 8048389:	85 d2                	test   %edx,%edx
 804838b:	74 05                	je     8048392 <_init+0x22>
 804838d:	e8 2e 00 00 00       	call   80483c0 <__gmon_start__@plt>
 8048392:	e8 09 01 00 00       	call   80484a0 <frame_dummy>
 8048397:	e8 44 03 00 00       	call   80486e0 <__do_global_ctors_aux>
 804839c:	58                   	pop    %eax
 804839d:	5b                   	pop    %ebx
 804839e:	c9                   	leave  
 804839f:	c3                   	ret    

Disassembly of section .plt:

080483a0 <getchar@plt-0x10>:
 80483a0:	ff 35 f8 9f 04 08    	pushl  0x8049ff8
 80483a6:	ff 25 fc 9f 04 08    	jmp    *0x8049ffc
 80483ac:	00 00                	add    %al,(%eax)
	...

080483b0 <getchar@plt>:
 80483b0:	ff 25 00 a0 04 08    	jmp    *0x804a000
 80483b6:	68 00 00 00 00       	push   $0x0
 80483bb:	e9 e0 ff ff ff       	jmp    80483a0 <_init+0x30>

080483c0 <__gmon_start__@plt>:
 80483c0:	ff 25 04 a0 04 08    	jmp    *0x804a004
 80483c6:	68 08 00 00 00       	push   $0x8
 80483cb:	e9 d0 ff ff ff       	jmp    80483a0 <_init+0x30>

080483d0 <__libc_start_main@plt>:
 80483d0:	ff 25 08 a0 04 08    	jmp    *0x804a008
 80483d6:	68 10 00 00 00       	push   $0x10
 80483db:	e9 c0 ff ff ff       	jmp    80483a0 <_init+0x30>

080483e0 <__ctype_b_loc@plt>:
 80483e0:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 80483e6:	68 18 00 00 00       	push   $0x18
 80483eb:	e9 b0 ff ff ff       	jmp    80483a0 <_init+0x30>

080483f0 <printf@plt>:
 80483f0:	ff 25 10 a0 04 08    	jmp    *0x804a010
 80483f6:	68 20 00 00 00       	push   $0x20
 80483fb:	e9 a0 ff ff ff       	jmp    80483a0 <_init+0x30>

08048400 <__stack_chk_fail@plt>:
 8048400:	ff 25 14 a0 04 08    	jmp    *0x804a014
 8048406:	68 28 00 00 00       	push   $0x28
 804840b:	e9 90 ff ff ff       	jmp    80483a0 <_init+0x30>

Disassembly of section .text:

08048410 <_start>:
 8048410:	31 ed                	xor    %ebp,%ebp
 8048412:	5e                   	pop    %esi
 8048413:	89 e1                	mov    %esp,%ecx
 8048415:	83 e4 f0             	and    $0xfffffff0,%esp
 8048418:	50                   	push   %eax
 8048419:	54                   	push   %esp
 804841a:	52                   	push   %edx
 804841b:	68 70 86 04 08       	push   $0x8048670
 8048420:	68 80 86 04 08       	push   $0x8048680
 8048425:	51                   	push   %ecx
 8048426:	56                   	push   %esi
 8048427:	68 f8 85 04 08       	push   $0x80485f8
 804842c:	e8 9f ff ff ff       	call   80483d0 <__libc_start_main@plt>
 8048431:	f4                   	hlt    
 8048432:	90                   	nop
 8048433:	90                   	nop
 8048434:	90                   	nop
 8048435:	90                   	nop
 8048436:	90                   	nop
 8048437:	90                   	nop
 8048438:	90                   	nop
 8048439:	90                   	nop
 804843a:	90                   	nop
 804843b:	90                   	nop
 804843c:	90                   	nop
 804843d:	90                   	nop
 804843e:	90                   	nop
 804843f:	90                   	nop

08048440 <__do_global_dtors_aux>:
 8048440:	55                   	push   %ebp
 8048441:	89 e5                	mov    %esp,%ebp
 8048443:	53                   	push   %ebx
 8048444:	83 ec 04             	sub    $0x4,%esp
 8048447:	80 3d 20 a0 04 08 00 	cmpb   $0x0,0x804a020
 804844e:	75 3f                	jne    804848f <__do_global_dtors_aux+0x4f>
 8048450:	a1 24 a0 04 08       	mov    0x804a024,%eax
 8048455:	bb 18 9f 04 08       	mov    $0x8049f18,%ebx
 804845a:	81 eb 14 9f 04 08    	sub    $0x8049f14,%ebx
 8048460:	c1 fb 02             	sar    $0x2,%ebx
 8048463:	83 eb 01             	sub    $0x1,%ebx
 8048466:	39 d8                	cmp    %ebx,%eax
 8048468:	73 1e                	jae    8048488 <__do_global_dtors_aux+0x48>
 804846a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8048470:	83 c0 01             	add    $0x1,%eax
 8048473:	a3 24 a0 04 08       	mov    %eax,0x804a024
 8048478:	ff 14 85 14 9f 04 08 	call   *0x8049f14(,%eax,4)
 804847f:	a1 24 a0 04 08       	mov    0x804a024,%eax
 8048484:	39 d8                	cmp    %ebx,%eax
 8048486:	72 e8                	jb     8048470 <__do_global_dtors_aux+0x30>
 8048488:	c6 05 20 a0 04 08 01 	movb   $0x1,0x804a020
 804848f:	83 c4 04             	add    $0x4,%esp
 8048492:	5b                   	pop    %ebx
 8048493:	5d                   	pop    %ebp
 8048494:	c3                   	ret    
 8048495:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048499:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

080484a0 <frame_dummy>:
 80484a0:	55                   	push   %ebp
 80484a1:	89 e5                	mov    %esp,%ebp
 80484a3:	83 ec 18             	sub    $0x18,%esp
 80484a6:	a1 1c 9f 04 08       	mov    0x8049f1c,%eax
 80484ab:	85 c0                	test   %eax,%eax
 80484ad:	74 12                	je     80484c1 <frame_dummy+0x21>
 80484af:	b8 00 00 00 00       	mov    $0x0,%eax
 80484b4:	85 c0                	test   %eax,%eax
 80484b6:	74 09                	je     80484c1 <frame_dummy+0x21>
 80484b8:	c7 04 24 1c 9f 04 08 	movl   $0x8049f1c,(%esp)
 80484bf:	ff d0                	call   *%eax
 80484c1:	c9                   	leave  
 80484c2:	c3                   	ret    
 80484c3:	90                   	nop

080484c4 <getxs>:
 80484c4:	55                   	push   %ebp
 80484c5:	89 e5                	mov    %esp,%ebp
 80484c7:	83 ec 28             	sub    $0x28,%esp
 80484ca:	c7 45 f0 01 00 00 00 	movl   $0x1,-0x10(%ebp)
 80484d1:	c7 45 ec 00 00 00 00 	movl   $0x0,-0x14(%ebp)
 80484d8:	8b 45 08             	mov    0x8(%ebp),%eax
 80484db:	89 45 e8             	mov    %eax,-0x18(%ebp)
 80484de:	e9 89 00 00 00       	jmp    804856c <getxs+0xa8>
 80484e3:	e8 f8 fe ff ff       	call   80483e0 <__ctype_b_loc@plt>
 80484e8:	8b 00                	mov    (%eax),%eax
 80484ea:	8b 55 f4             	mov    -0xc(%ebp),%edx
 80484ed:	01 d2                	add    %edx,%edx
 80484ef:	01 d0                	add    %edx,%eax
 80484f1:	0f b7 00             	movzwl (%eax),%eax
 80484f4:	0f b7 c0             	movzwl %ax,%eax
 80484f7:	25 00 10 00 00       	and    $0x1000,%eax
 80484fc:	85 c0                	test   %eax,%eax
 80484fe:	74 6c                	je     804856c <getxs+0xa8>
 8048500:	83 7d f4 2f          	cmpl   $0x2f,-0xc(%ebp)
 8048504:	7e 11                	jle    8048517 <getxs+0x53>
 8048506:	83 7d f4 39          	cmpl   $0x39,-0xc(%ebp)
 804850a:	7f 0b                	jg     8048517 <getxs+0x53>
 804850c:	8b 45 f4             	mov    -0xc(%ebp),%eax
 804850f:	83 e8 30             	sub    $0x30,%eax
 8048512:	89 45 e4             	mov    %eax,-0x1c(%ebp)
 8048515:	eb 20                	jmp    8048537 <getxs+0x73>
 8048517:	83 7d f4 40          	cmpl   $0x40,-0xc(%ebp)
 804851b:	7e 11                	jle    804852e <getxs+0x6a>
 804851d:	83 7d f4 46          	cmpl   $0x46,-0xc(%ebp)
 8048521:	7f 0b                	jg     804852e <getxs+0x6a>
 8048523:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8048526:	83 e8 37             	sub    $0x37,%eax
 8048529:	89 45 e4             	mov    %eax,-0x1c(%ebp)
 804852c:	eb 09                	jmp    8048537 <getxs+0x73>
 804852e:	8b 45 f4             	mov    -0xc(%ebp),%eax
 8048531:	83 e8 57             	sub    $0x57,%eax
 8048534:	89 45 e4             	mov    %eax,-0x1c(%ebp)
 8048537:	83 7d f0 00          	cmpl   $0x0,-0x10(%ebp)
 804853b:	74 0f                	je     804854c <getxs+0x88>
 804853d:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 8048540:	89 45 ec             	mov    %eax,-0x14(%ebp)
 8048543:	c7 45 f0 00 00 00 00 	movl   $0x0,-0x10(%ebp)
 804854a:	eb 20                	jmp    804856c <getxs+0xa8>
 804854c:	8b 45 ec             	mov    -0x14(%ebp),%eax
 804854f:	89 c2                	mov    %eax,%edx
 8048551:	c1 e2 04             	shl    $0x4,%edx
 8048554:	8b 45 e4             	mov    -0x1c(%ebp),%eax
 8048557:	8d 04 02             	lea    (%edx,%eax,1),%eax
 804855a:	89 c2                	mov    %eax,%edx
 804855c:	8b 45 e8             	mov    -0x18(%ebp),%eax
 804855f:	88 10                	mov    %dl,(%eax)
 8048561:	83 45 e8 01          	addl   $0x1,-0x18(%ebp)
 8048565:	c7 45 f0 01 00 00 00 	movl   $0x1,-0x10(%ebp)
 804856c:	e8 3f fe ff ff       	call   80483b0 <getchar@plt>
 8048571:	89 45 f4             	mov    %eax,-0xc(%ebp)
 8048574:	83 7d f4 ff          	cmpl   $0xffffffff,-0xc(%ebp)
 8048578:	74 0a                	je     8048584 <getxs+0xc0>
 804857a:	83 7d f4 0a          	cmpl   $0xa,-0xc(%ebp)
 804857e:	0f 85 5f ff ff ff    	jne    80484e3 <getxs+0x1f>
 8048584:	8b 45 e8             	mov    -0x18(%ebp),%eax
 8048587:	c6 00 00             	movb   $0x0,(%eax)
 804858a:	83 45 e8 01          	addl   $0x1,-0x18(%ebp)
 804858e:	8b 45 08             	mov    0x8(%ebp),%eax
 8048591:	c9                   	leave  
 8048592:	c3                   	ret    

08048593 <getbuf>:
 8048593:	55                   	push   %ebp
 8048594:	89 e5                	mov    %esp,%ebp
 8048596:	83 ec 28             	sub    $0x28,%esp
 8048599:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 804859f:	89 45 f4             	mov    %eax,-0xc(%ebp)
 80485a2:	31 c0                	xor    %eax,%eax
 80485a4:	8d 45 e8             	lea    -0x18(%ebp),%eax
 80485a7:	89 04 24             	mov    %eax,(%esp)
 80485aa:	e8 15 ff ff ff       	call   80484c4 <getxs>
 80485af:	b8 01 00 00 00       	mov    $0x1,%eax
 80485b4:	8b 55 f4             	mov    -0xc(%ebp),%edx
 80485b7:	65 33 15 14 00 00 00 	xor    %gs:0x14,%edx
 80485be:	74 05                	je     80485c5 <getbuf+0x32>
 80485c0:	e8 3b fe ff ff       	call   8048400 <__stack_chk_fail@plt>
 80485c5:	c9                   	leave  
 80485c6:	c3                   	ret    

080485c7 <test>:
 80485c7:	55                   	push   %ebp
 80485c8:	89 e5                	mov    %esp,%ebp
 80485ca:	83 ec 28             	sub    $0x28,%esp
 80485cd:	b8 30 87 04 08       	mov    $0x8048730,%eax
 80485d2:	89 04 24             	mov    %eax,(%esp)
 80485d5:	e8 16 fe ff ff       	call   80483f0 <printf@plt>
 80485da:	e8 b4 ff ff ff       	call   8048593 <getbuf>
 80485df:	89 45 f4             	mov    %eax,-0xc(%ebp)
 80485e2:	b8 41 87 04 08       	mov    $0x8048741,%eax
 80485e7:	8b 55 f4             	mov    -0xc(%ebp),%edx
 80485ea:	89 54 24 04          	mov    %edx,0x4(%esp)
 80485ee:	89 04 24             	mov    %eax,(%esp)
 80485f1:	e8 fa fd ff ff       	call   80483f0 <printf@plt>
 80485f6:	c9                   	leave  
 80485f7:	c3                   	ret    

080485f8 <main>:
 80485f8:	8d 4c 24 04          	lea    0x4(%esp),%ecx
 80485fc:	83 e4 f0             	and    $0xfffffff0,%esp
 80485ff:	ff 71 fc             	pushl  -0x4(%ecx)
 8048602:	55                   	push   %ebp
 8048603:	89 e5                	mov    %esp,%ebp
 8048605:	51                   	push   %ecx
 8048606:	83 ec 54             	sub    $0x54,%esp
 8048609:	65 a1 14 00 00 00    	mov    %gs:0x14,%eax
 804860f:	89 45 f4             	mov    %eax,-0xc(%ebp)
 8048612:	31 c0                	xor    %eax,%eax
 8048614:	8d 45 ac             	lea    -0x54(%ebp),%eax
 8048617:	25 ff 0f 00 00       	and    $0xfff,%eax
 804861c:	89 45 f0             	mov    %eax,-0x10(%ebp)
 804861f:	8b 45 f0             	mov    -0x10(%ebp),%eax
 8048622:	83 c0 0f             	add    $0xf,%eax
 8048625:	83 c0 0f             	add    $0xf,%eax
 8048628:	c1 e8 04             	shr    $0x4,%eax
 804862b:	c1 e0 04             	shl    $0x4,%eax
 804862e:	29 c4                	sub    %eax,%esp
 8048630:	89 e0                	mov    %esp,%eax
 8048632:	83 c0 0f             	add    $0xf,%eax
 8048635:	c1 e8 04             	shr    $0x4,%eax
 8048638:	c1 e0 04             	shl    $0x4,%eax
 804863b:	89 45 ec             	mov    %eax,-0x14(%ebp)
 804863e:	8b 45 ec             	mov    -0x14(%ebp),%eax
 8048641:	c7 00 00 00 00 00    	movl   $0x0,(%eax)
 8048647:	e8 7b ff ff ff       	call   80485c7 <test>
 804864c:	b8 00 00 00 00       	mov    $0x0,%eax
 8048651:	8b 55 f4             	mov    -0xc(%ebp),%edx
 8048654:	65 33 15 14 00 00 00 	xor    %gs:0x14,%edx
 804865b:	74 05                	je     8048662 <main+0x6a>
 804865d:	e8 9e fd ff ff       	call   8048400 <__stack_chk_fail@plt>
 8048662:	8b 4d fc             	mov    -0x4(%ebp),%ecx
 8048665:	c9                   	leave  
 8048666:	8d 61 fc             	lea    -0x4(%ecx),%esp
 8048669:	c3                   	ret    
 804866a:	90                   	nop
 804866b:	90                   	nop
 804866c:	90                   	nop
 804866d:	90                   	nop
 804866e:	90                   	nop
 804866f:	90                   	nop

08048670 <__libc_csu_fini>:
 8048670:	55                   	push   %ebp
 8048671:	89 e5                	mov    %esp,%ebp
 8048673:	5d                   	pop    %ebp
 8048674:	c3                   	ret    
 8048675:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048679:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048680 <__libc_csu_init>:
 8048680:	55                   	push   %ebp
 8048681:	89 e5                	mov    %esp,%ebp
 8048683:	57                   	push   %edi
 8048684:	56                   	push   %esi
 8048685:	53                   	push   %ebx
 8048686:	e8 4f 00 00 00       	call   80486da <__i686.get_pc_thunk.bx>
 804868b:	81 c3 69 19 00 00    	add    $0x1969,%ebx
 8048691:	83 ec 1c             	sub    $0x1c,%esp
 8048694:	e8 d7 fc ff ff       	call   8048370 <_init>
 8048699:	8d bb 18 ff ff ff    	lea    -0xe8(%ebx),%edi
 804869f:	8d 83 18 ff ff ff    	lea    -0xe8(%ebx),%eax
 80486a5:	29 c7                	sub    %eax,%edi
 80486a7:	c1 ff 02             	sar    $0x2,%edi
 80486aa:	85 ff                	test   %edi,%edi
 80486ac:	74 24                	je     80486d2 <__libc_csu_init+0x52>
 80486ae:	31 f6                	xor    %esi,%esi
 80486b0:	8b 45 10             	mov    0x10(%ebp),%eax
 80486b3:	89 44 24 08          	mov    %eax,0x8(%esp)
 80486b7:	8b 45 0c             	mov    0xc(%ebp),%eax
 80486ba:	89 44 24 04          	mov    %eax,0x4(%esp)
 80486be:	8b 45 08             	mov    0x8(%ebp),%eax
 80486c1:	89 04 24             	mov    %eax,(%esp)
 80486c4:	ff 94 b3 18 ff ff ff 	call   *-0xe8(%ebx,%esi,4)
 80486cb:	83 c6 01             	add    $0x1,%esi
 80486ce:	39 fe                	cmp    %edi,%esi
 80486d0:	72 de                	jb     80486b0 <__libc_csu_init+0x30>
 80486d2:	83 c4 1c             	add    $0x1c,%esp
 80486d5:	5b                   	pop    %ebx
 80486d6:	5e                   	pop    %esi
 80486d7:	5f                   	pop    %edi
 80486d8:	5d                   	pop    %ebp
 80486d9:	c3                   	ret    

080486da <__i686.get_pc_thunk.bx>:
 80486da:	8b 1c 24             	mov    (%esp),%ebx
 80486dd:	c3                   	ret    
 80486de:	90                   	nop
 80486df:	90                   	nop

080486e0 <__do_global_ctors_aux>:
 80486e0:	55                   	push   %ebp
 80486e1:	89 e5                	mov    %esp,%ebp
 80486e3:	53                   	push   %ebx
 80486e4:	83 ec 04             	sub    $0x4,%esp
 80486e7:	a1 0c 9f 04 08       	mov    0x8049f0c,%eax
 80486ec:	83 f8 ff             	cmp    $0xffffffff,%eax
 80486ef:	74 13                	je     8048704 <__do_global_ctors_aux+0x24>
 80486f1:	bb 0c 9f 04 08       	mov    $0x8049f0c,%ebx
 80486f6:	66 90                	xchg   %ax,%ax
 80486f8:	83 eb 04             	sub    $0x4,%ebx
 80486fb:	ff d0                	call   *%eax
 80486fd:	8b 03                	mov    (%ebx),%eax
 80486ff:	83 f8 ff             	cmp    $0xffffffff,%eax
 8048702:	75 f4                	jne    80486f8 <__do_global_ctors_aux+0x18>
 8048704:	83 c4 04             	add    $0x4,%esp
 8048707:	5b                   	pop    %ebx
 8048708:	5d                   	pop    %ebp
 8048709:	c3                   	ret    
 804870a:	90                   	nop
 804870b:	90                   	nop

Disassembly of section .fini:

0804870c <_fini>:
 804870c:	55                   	push   %ebp
 804870d:	89 e5                	mov    %esp,%ebp
 804870f:	53                   	push   %ebx
 8048710:	83 ec 04             	sub    $0x4,%esp
 8048713:	e8 00 00 00 00       	call   8048718 <_fini+0xc>
 8048718:	5b                   	pop    %ebx
 8048719:	81 c3 dc 18 00 00    	add    $0x18dc,%ebx
 804871f:	e8 1c fd ff ff       	call   8048440 <__do_global_dtors_aux>
 8048724:	59                   	pop    %ecx
 8048725:	5b                   	pop    %ebx
 8048726:	c9                   	leave  
 8048727:	c3                   	ret    
