
test:     file format elf32-i386


Disassembly of section .init:

08048318 <_init>:
 8048318:	53                   	push   %ebx
 8048319:	83 ec 08             	sub    $0x8,%esp
 804831c:	e8 00 00 00 00       	call   8048321 <_init+0x9>
 8048321:	5b                   	pop    %ebx
 8048322:	81 c3 d3 1c 00 00    	add    $0x1cd3,%ebx
 8048328:	8b 83 fc ff ff ff    	mov    -0x4(%ebx),%eax
 804832e:	85 c0                	test   %eax,%eax
 8048330:	74 05                	je     8048337 <_init+0x1f>
 8048332:	e8 49 00 00 00       	call   8048380 <__gmon_start__@plt>
 8048337:	e8 04 01 00 00       	call   8048440 <frame_dummy>
 804833c:	e8 8f 03 00 00       	call   80486d0 <__do_global_ctors_aux>
 8048341:	83 c4 08             	add    $0x8,%esp
 8048344:	5b                   	pop    %ebx
 8048345:	c3                   	ret    

Disassembly of section .plt:

08048350 <printf@plt-0x10>:
 8048350:	ff 35 f8 9f 04 08    	pushl  0x8049ff8
 8048356:	ff 25 fc 9f 04 08    	jmp    *0x8049ffc
 804835c:	00 00                	add    %al,(%eax)
	...

08048360 <printf@plt>:
 8048360:	ff 25 00 a0 04 08    	jmp    *0x804a000
 8048366:	68 00 00 00 00       	push   $0x0
 804836b:	e9 e0 ff ff ff       	jmp    8048350 <_init+0x38>

08048370 <getchar@plt>:
 8048370:	ff 25 04 a0 04 08    	jmp    *0x804a004
 8048376:	68 08 00 00 00       	push   $0x8
 804837b:	e9 d0 ff ff ff       	jmp    8048350 <_init+0x38>

08048380 <__gmon_start__@plt>:
 8048380:	ff 25 08 a0 04 08    	jmp    *0x804a008
 8048386:	68 10 00 00 00       	push   $0x10
 804838b:	e9 c0 ff ff ff       	jmp    8048350 <_init+0x38>

08048390 <__libc_start_main@plt>:
 8048390:	ff 25 0c a0 04 08    	jmp    *0x804a00c
 8048396:	68 18 00 00 00       	push   $0x18
 804839b:	e9 b0 ff ff ff       	jmp    8048350 <_init+0x38>

080483a0 <__ctype_b_loc@plt>:
 80483a0:	ff 25 10 a0 04 08    	jmp    *0x804a010
 80483a6:	68 20 00 00 00       	push   $0x20
 80483ab:	e9 a0 ff ff ff       	jmp    8048350 <_init+0x38>

Disassembly of section .text:

080483b0 <_start>:
 80483b0:	31 ed                	xor    %ebp,%ebp
 80483b2:	5e                   	pop    %esi
 80483b3:	89 e1                	mov    %esp,%ecx
 80483b5:	83 e4 f0             	and    $0xfffffff0,%esp
 80483b8:	50                   	push   %eax
 80483b9:	54                   	push   %esp
 80483ba:	52                   	push   %edx
 80483bb:	68 c0 86 04 08       	push   $0x80486c0
 80483c0:	68 50 86 04 08       	push   $0x8048650
 80483c5:	51                   	push   %ecx
 80483c6:	56                   	push   %esi
 80483c7:	68 f7 85 04 08       	push   $0x80485f7
 80483cc:	e8 bf ff ff ff       	call   8048390 <__libc_start_main@plt>
 80483d1:	f4                   	hlt    
 80483d2:	90                   	nop
 80483d3:	90                   	nop
 80483d4:	90                   	nop
 80483d5:	90                   	nop
 80483d6:	90                   	nop
 80483d7:	90                   	nop
 80483d8:	90                   	nop
 80483d9:	90                   	nop
 80483da:	90                   	nop
 80483db:	90                   	nop
 80483dc:	90                   	nop
 80483dd:	90                   	nop
 80483de:	90                   	nop
 80483df:	90                   	nop

080483e0 <__do_global_dtors_aux>:
 80483e0:	55                   	push   %ebp
 80483e1:	89 e5                	mov    %esp,%ebp
 80483e3:	53                   	push   %ebx
 80483e4:	83 ec 04             	sub    $0x4,%esp
 80483e7:	80 3d 1c a0 04 08 00 	cmpb   $0x0,0x804a01c
 80483ee:	75 3f                	jne    804842f <__do_global_dtors_aux+0x4f>
 80483f0:	a1 20 a0 04 08       	mov    0x804a020,%eax
 80483f5:	bb 20 9f 04 08       	mov    $0x8049f20,%ebx
 80483fa:	81 eb 1c 9f 04 08    	sub    $0x8049f1c,%ebx
 8048400:	c1 fb 02             	sar    $0x2,%ebx
 8048403:	83 eb 01             	sub    $0x1,%ebx
 8048406:	39 d8                	cmp    %ebx,%eax
 8048408:	73 1e                	jae    8048428 <__do_global_dtors_aux+0x48>
 804840a:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8048410:	83 c0 01             	add    $0x1,%eax
 8048413:	a3 20 a0 04 08       	mov    %eax,0x804a020
 8048418:	ff 14 85 1c 9f 04 08 	call   *0x8049f1c(,%eax,4)
 804841f:	a1 20 a0 04 08       	mov    0x804a020,%eax
 8048424:	39 d8                	cmp    %ebx,%eax
 8048426:	72 e8                	jb     8048410 <__do_global_dtors_aux+0x30>
 8048428:	c6 05 1c a0 04 08 01 	movb   $0x1,0x804a01c
 804842f:	83 c4 04             	add    $0x4,%esp
 8048432:	5b                   	pop    %ebx
 8048433:	5d                   	pop    %ebp
 8048434:	c3                   	ret    
 8048435:	8d 74 26 00          	lea    0x0(%esi,%eiz,1),%esi
 8048439:	8d bc 27 00 00 00 00 	lea    0x0(%edi,%eiz,1),%edi

08048440 <frame_dummy>:
 8048440:	55                   	push   %ebp
 8048441:	89 e5                	mov    %esp,%ebp
 8048443:	83 ec 18             	sub    $0x18,%esp
 8048446:	a1 24 9f 04 08       	mov    0x8049f24,%eax
 804844b:	85 c0                	test   %eax,%eax
 804844d:	74 12                	je     8048461 <frame_dummy+0x21>
 804844f:	b8 00 00 00 00       	mov    $0x0,%eax
 8048454:	85 c0                	test   %eax,%eax
 8048456:	74 09                	je     8048461 <frame_dummy+0x21>
 8048458:	c7 04 24 24 9f 04 08 	movl   $0x8049f24,(%esp)
 804845f:	ff d0                	call   *%eax
 8048461:	c9                   	leave  
 8048462:	c3                   	ret    
 8048463:	90                   	nop

08048464 <function>:
 8048464:	55                   	push   %ebp
 8048465:	89 e5                	mov    %esp,%ebp
 8048467:	a1 34 a0 04 08       	mov    0x804a034,%eax
 804846c:	85 c0                	test   %eax,%eax
 804846e:	74 27                	je     8048497 <function+0x33>
 8048470:	83 f8 0d             	cmp    $0xd,%eax
 8048473:	74 13                	je     8048488 <function+0x24>
 8048475:	eb 2b                	jmp    80484a2 <function+0x3e>
 8048477:	c7 05 34 a0 04 08 0d 	movl   $0xd,0x804a034
 804847e:	00 00 00 
 8048481:	a1 38 a0 04 08       	mov    0x804a038,%eax
 8048486:	eb 1a                	jmp    80484a2 <function+0x3e>
 8048488:	a1 38 a0 04 08       	mov    0x804a038,%eax
 804848d:	83 c0 01             	add    $0x1,%eax
 8048490:	a3 38 a0 04 08       	mov    %eax,0x804a038
 8048495:	eb 01                	jmp    8048498 <function+0x34>
 8048497:	90                   	nop
 8048498:	a1 38 a0 04 08       	mov    0x804a038,%eax
 804849d:	83 f8 09             	cmp    $0x9,%eax
 80484a0:	7e d5                	jle    8048477 <function+0x13>
 80484a2:	5d                   	pop    %ebp
 80484a3:	c3                   	ret    

080484a4 <decompressor>:
 80484a4:	55                   	push   %ebp
 80484a5:	89 e5                	mov    %esp,%ebp
 80484a7:	83 ec 08             	sub    $0x8,%esp
 80484aa:	a1 28 a0 04 08       	mov    0x804a028,%eax
 80484af:	83 f8 1d             	cmp    $0x1d,%eax
 80484b2:	74 57                	je     804850b <decompressor+0x67>
 80484b4:	83 f8 1f             	cmp    $0x1f,%eax
 80484b7:	74 0a                	je     80484c3 <decompressor+0x1f>
 80484b9:	85 c0                	test   %eax,%eax
 80484bb:	0f 85 87 00 00 00    	jne    8048548 <decompressor+0xa4>
 80484c1:	eb 01                	jmp    80484c4 <decompressor+0x20>
 80484c3:	90                   	nop
 80484c4:	e8 a7 fe ff ff       	call   8048370 <getchar@plt>
 80484c9:	a3 2c a0 04 08       	mov    %eax,0x804a02c
 80484ce:	a1 2c a0 04 08       	mov    0x804a02c,%eax
 80484d3:	83 f8 ff             	cmp    $0xffffffff,%eax
 80484d6:	74 5e                	je     8048536 <decompressor+0x92>
 80484d8:	a1 2c a0 04 08       	mov    0x804a02c,%eax
 80484dd:	3d ff 00 00 00       	cmp    $0xff,%eax
 80484e2:	75 3f                	jne    8048523 <decompressor+0x7f>
 80484e4:	e8 87 fe ff ff       	call   8048370 <getchar@plt>
 80484e9:	a3 30 a0 04 08       	mov    %eax,0x804a030
 80484ee:	e8 7d fe ff ff       	call   8048370 <getchar@plt>
 80484f3:	a3 2c a0 04 08       	mov    %eax,0x804a02c
 80484f8:	eb 11                	jmp    804850b <decompressor+0x67>
 80484fa:	c7 05 28 a0 04 08 1d 	movl   $0x1d,0x804a028
 8048501:	00 00 00 
 8048504:	a1 2c a0 04 08       	mov    0x804a02c,%eax
 8048509:	eb 3f                	jmp    804854a <decompressor+0xa6>
 804850b:	a1 30 a0 04 08       	mov    0x804a030,%eax
 8048510:	85 c0                	test   %eax,%eax
 8048512:	0f 95 c2             	setne  %dl
 8048515:	83 e8 01             	sub    $0x1,%eax
 8048518:	a3 30 a0 04 08       	mov    %eax,0x804a030
 804851d:	84 d2                	test   %dl,%dl
 804851f:	75 d9                	jne    80484fa <decompressor+0x56>
 8048521:	eb 11                	jmp    8048534 <decompressor+0x90>
 8048523:	c7 05 28 a0 04 08 1f 	movl   $0x1f,0x804a028
 804852a:	00 00 00 
 804852d:	a1 2c a0 04 08       	mov    0x804a02c,%eax
 8048532:	eb 16                	jmp    804854a <decompressor+0xa6>
 8048534:	eb 8d                	jmp    80484c3 <decompressor+0x1f>
 8048536:	90                   	nop
 8048537:	c7 05 28 a0 04 08 21 	movl   $0x21,0x804a028
 804853e:	00 00 00 
 8048541:	b8 ff ff ff ff       	mov    $0xffffffff,%eax
 8048546:	eb 02                	jmp    804854a <decompressor+0xa6>
 8048548:	eb 00                	jmp    804854a <decompressor+0xa6>
 804854a:	c9                   	leave  
 804854b:	c3                   	ret    

0804854c <parser>:
 804854c:	55                   	push   %ebp
 804854d:	89 e5                	mov    %esp,%ebp
 804854f:	83 ec 18             	sub    $0x18,%esp
 8048552:	a1 24 a0 04 08       	mov    0x804a024,%eax
 8048557:	83 f8 34             	cmp    $0x34,%eax
 804855a:	74 17                	je     8048573 <parser+0x27>
 804855c:	83 f8 34             	cmp    $0x34,%eax
 804855f:	0f 8f 90 00 00 00    	jg     80485f5 <parser+0xa9>
 8048565:	85 c0                	test   %eax,%eax
 8048567:	74 0b                	je     8048574 <parser+0x28>
 8048569:	83 f8 2d             	cmp    $0x2d,%eax
 804856c:	74 49                	je     80485b7 <parser+0x6b>
 804856e:	e9 82 00 00 00       	jmp    80485f5 <parser+0xa9>
 8048573:	90                   	nop
 8048574:	83 7d 08 ff          	cmpl   $0xffffffff,0x8(%ebp)
 8048578:	74 7a                	je     80485f4 <parser+0xa8>
 804857a:	e8 21 fe ff ff       	call   80483a0 <__ctype_b_loc@plt>
 804857f:	8b 00                	mov    (%eax),%eax
 8048581:	8b 55 08             	mov    0x8(%ebp),%edx
 8048584:	01 d2                	add    %edx,%edx
 8048586:	01 d0                	add    %edx,%eax
 8048588:	0f b7 00             	movzwl (%eax),%eax
 804858b:	0f b7 c0             	movzwl %ax,%eax
 804858e:	25 00 04 00 00       	and    $0x400,%eax
 8048593:	85 c0                	test   %eax,%eax
 8048595:	74 3d                	je     80485d4 <parser+0x88>
 8048597:	b8 20 87 04 08       	mov    $0x8048720,%eax
 804859c:	8b 55 08             	mov    0x8(%ebp),%edx
 804859f:	89 54 24 04          	mov    %edx,0x4(%esp)
 80485a3:	89 04 24             	mov    %eax,(%esp)
 80485a6:	e8 b5 fd ff ff       	call   8048360 <printf@plt>
 80485ab:	c7 05 24 a0 04 08 2d 	movl   $0x2d,0x804a024
 80485b2:	00 00 00 
 80485b5:	eb 3e                	jmp    80485f5 <parser+0xa9>
 80485b7:	e8 e4 fd ff ff       	call   80483a0 <__ctype_b_loc@plt>
 80485bc:	8b 00                	mov    (%eax),%eax
 80485be:	8b 55 08             	mov    0x8(%ebp),%edx
 80485c1:	01 d2                	add    %edx,%edx
 80485c3:	01 d0                	add    %edx,%eax
 80485c5:	0f b7 00             	movzwl (%eax),%eax
 80485c8:	0f b7 c0             	movzwl %ax,%eax
 80485cb:	25 00 04 00 00       	and    $0x400,%eax
 80485d0:	85 c0                	test   %eax,%eax
 80485d2:	75 c3                	jne    8048597 <parser+0x4b>
 80485d4:	b8 20 87 04 08       	mov    $0x8048720,%eax
 80485d9:	8b 55 08             	mov    0x8(%ebp),%edx
 80485dc:	89 54 24 04          	mov    %edx,0x4(%esp)
 80485e0:	89 04 24             	mov    %eax,(%esp)
 80485e3:	e8 78 fd ff ff       	call   8048360 <printf@plt>
 80485e8:	c7 05 24 a0 04 08 34 	movl   $0x34,0x804a024
 80485ef:	00 00 00 
 80485f2:	eb 01                	jmp    80485f5 <parser+0xa9>
 80485f4:	90                   	nop
 80485f5:	c9                   	leave  
 80485f6:	c3                   	ret    

080485f7 <main>:
 80485f7:	55                   	push   %ebp
 80485f8:	89 e5                	mov    %esp,%ebp
 80485fa:	83 e4 f0             	and    $0xfffffff0,%esp
 80485fd:	83 ec 20             	sub    $0x20,%esp
 8048600:	c7 44 24 1c 00 00 00 	movl   $0x0,0x1c(%esp)
 8048607:	00 
 8048608:	c7 44 24 1c 00 00 00 	movl   $0x0,0x1c(%esp)
 804860f:	00 
 8048610:	eb 1b                	jmp    804862d <main+0x36>
 8048612:	e8 4d fe ff ff       	call   8048464 <function>
 8048617:	ba 24 87 04 08       	mov    $0x8048724,%edx
 804861c:	89 44 24 04          	mov    %eax,0x4(%esp)
 8048620:	89 14 24             	mov    %edx,(%esp)
 8048623:	e8 38 fd ff ff       	call   8048360 <printf@plt>
 8048628:	83 44 24 1c 01       	addl   $0x1,0x1c(%esp)
 804862d:	83 7c 24 1c 09       	cmpl   $0x9,0x1c(%esp)
 8048632:	7e de                	jle    8048612 <main+0x1b>
 8048634:	e8 6b fe ff ff       	call   80484a4 <decompressor>
 8048639:	89 04 24             	mov    %eax,(%esp)
 804863c:	e8 0b ff ff ff       	call   804854c <parser>
 8048641:	eb f1                	jmp    8048634 <main+0x3d>
 8048643:	90                   	nop
 8048644:	90                   	nop
 8048645:	90                   	nop
 8048646:	90                   	nop
 8048647:	90                   	nop
 8048648:	90                   	nop
 8048649:	90                   	nop
 804864a:	90                   	nop
 804864b:	90                   	nop
 804864c:	90                   	nop
 804864d:	90                   	nop
 804864e:	90                   	nop
 804864f:	90                   	nop

08048650 <__libc_csu_init>:
 8048650:	55                   	push   %ebp
 8048651:	57                   	push   %edi
 8048652:	56                   	push   %esi
 8048653:	53                   	push   %ebx
 8048654:	e8 69 00 00 00       	call   80486c2 <__i686.get_pc_thunk.bx>
 8048659:	81 c3 9b 19 00 00    	add    $0x199b,%ebx
 804865f:	83 ec 1c             	sub    $0x1c,%esp
 8048662:	8b 6c 24 30          	mov    0x30(%esp),%ebp
 8048666:	8d bb 20 ff ff ff    	lea    -0xe0(%ebx),%edi
 804866c:	e8 a7 fc ff ff       	call   8048318 <_init>
 8048671:	8d 83 20 ff ff ff    	lea    -0xe0(%ebx),%eax
 8048677:	29 c7                	sub    %eax,%edi
 8048679:	c1 ff 02             	sar    $0x2,%edi
 804867c:	85 ff                	test   %edi,%edi
 804867e:	74 29                	je     80486a9 <__libc_csu_init+0x59>
 8048680:	31 f6                	xor    %esi,%esi
 8048682:	8d b6 00 00 00 00    	lea    0x0(%esi),%esi
 8048688:	8b 44 24 38          	mov    0x38(%esp),%eax
 804868c:	89 2c 24             	mov    %ebp,(%esp)
 804868f:	89 44 24 08          	mov    %eax,0x8(%esp)
 8048693:	8b 44 24 34          	mov    0x34(%esp),%eax
 8048697:	89 44 24 04          	mov    %eax,0x4(%esp)
 804869b:	ff 94 b3 20 ff ff ff 	call   *-0xe0(%ebx,%esi,4)
 80486a2:	83 c6 01             	add    $0x1,%esi
 80486a5:	39 fe                	cmp    %edi,%esi
 80486a7:	75 df                	jne    8048688 <__libc_csu_init+0x38>
 80486a9:	83 c4 1c             	add    $0x1c,%esp
 80486ac:	5b                   	pop    %ebx
 80486ad:	5e                   	pop    %esi
 80486ae:	5f                   	pop    %edi
 80486af:	5d                   	pop    %ebp
 80486b0:	c3                   	ret    
 80486b1:	eb 0d                	jmp    80486c0 <__libc_csu_fini>
 80486b3:	90                   	nop
 80486b4:	90                   	nop
 80486b5:	90                   	nop
 80486b6:	90                   	nop
 80486b7:	90                   	nop
 80486b8:	90                   	nop
 80486b9:	90                   	nop
 80486ba:	90                   	nop
 80486bb:	90                   	nop
 80486bc:	90                   	nop
 80486bd:	90                   	nop
 80486be:	90                   	nop
 80486bf:	90                   	nop

080486c0 <__libc_csu_fini>:
 80486c0:	f3 c3                	repz ret 

080486c2 <__i686.get_pc_thunk.bx>:
 80486c2:	8b 1c 24             	mov    (%esp),%ebx
 80486c5:	c3                   	ret    
 80486c6:	90                   	nop
 80486c7:	90                   	nop
 80486c8:	90                   	nop
 80486c9:	90                   	nop
 80486ca:	90                   	nop
 80486cb:	90                   	nop
 80486cc:	90                   	nop
 80486cd:	90                   	nop
 80486ce:	90                   	nop
 80486cf:	90                   	nop

080486d0 <__do_global_ctors_aux>:
 80486d0:	55                   	push   %ebp
 80486d1:	89 e5                	mov    %esp,%ebp
 80486d3:	53                   	push   %ebx
 80486d4:	83 ec 04             	sub    $0x4,%esp
 80486d7:	a1 14 9f 04 08       	mov    0x8049f14,%eax
 80486dc:	83 f8 ff             	cmp    $0xffffffff,%eax
 80486df:	74 13                	je     80486f4 <__do_global_ctors_aux+0x24>
 80486e1:	bb 14 9f 04 08       	mov    $0x8049f14,%ebx
 80486e6:	66 90                	xchg   %ax,%ax
 80486e8:	83 eb 04             	sub    $0x4,%ebx
 80486eb:	ff d0                	call   *%eax
 80486ed:	8b 03                	mov    (%ebx),%eax
 80486ef:	83 f8 ff             	cmp    $0xffffffff,%eax
 80486f2:	75 f4                	jne    80486e8 <__do_global_ctors_aux+0x18>
 80486f4:	83 c4 04             	add    $0x4,%esp
 80486f7:	5b                   	pop    %ebx
 80486f8:	5d                   	pop    %ebp
 80486f9:	c3                   	ret    
 80486fa:	90                   	nop
 80486fb:	90                   	nop

Disassembly of section .fini:

080486fc <_fini>:
 80486fc:	53                   	push   %ebx
 80486fd:	83 ec 08             	sub    $0x8,%esp
 8048700:	e8 00 00 00 00       	call   8048705 <_fini+0x9>
 8048705:	5b                   	pop    %ebx
 8048706:	81 c3 ef 18 00 00    	add    $0x18ef,%ebx
 804870c:	e8 cf fc ff ff       	call   80483e0 <__do_global_dtors_aux>
 8048711:	83 c4 08             	add    $0x8,%esp
 8048714:	5b                   	pop    %ebx
 8048715:	c3                   	ret    
