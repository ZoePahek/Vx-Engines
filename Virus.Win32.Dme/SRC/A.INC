; ��������� ����. ��룠�� �� Jump��, ४��ᨢ�� ��室�� CALL'�.
; ������� ����� ����-������

Analyse	proc			; ESi - Entry point
	Call	CheckBlock	; �� ��� 㦥 �뫨 ? �᫨ �� - �� ��室
	jnc	XRet		; ���� �㤥� ����� � ४��ᨥ� � 横����

	Call	GetSize32	; ������ ��������
	push	eax
	Call	AddBlock	; ������� ���� ����

	Call	AddData		; �஢�ਬ �� �����

	mov	al,[esi]

	cmp	al,0C3h		; Ret ?
	jz	GRet

	cmp	al,0EBh		; Jmp short ?
	jz	aJmps

	cmp	al,0E8h		; Call near
	jz	aCalln

	cmp	al,0E9h		; Jmp near
	jz	aJmpn

	cmp	al,070h		; Jzz ?
	jb	t1
	cmp	al,07Fh
	jbe	cJmps

t1:	cmp	al,0E0h		; LOOPzz ?
	jb	t2
	cmp	al,0E2h
	jbe	cJmps

t2:	cmp	al,0Fh		; Extended Jzz ?
	jnz	SkipJ
	
	mov	al,[esi][1]

	cmp	al,80h
	jb	SkipJ
	cmp	al,8Fh
	jbe	cJmpn
	
SkipJ:	pop	eax
	add	esi,eax
	jmp	Analyse
GRet:	pop	eax
XRet:	ret
Analyse	endp

aJmps:	pop	eax
	Call	AddJump
	xor	eax,eax
	lodsb
	lodsb
	cbw
	or	ax,ax
	jge	NoIn2
	or	eax,0FFFF0000h	
NoIn2:	add	esi,eax
	jmp	Analyse

cJmps:	pop	eax
	Call	AddJump
	xor	eax,eax
	lodsb
	lodsb
	cbw
	or	ax,ax
	jge	NoIn3
	or	eax,0FFFF0000h
NoIn3:	push	esi
	add	esi,eax
	Call	Analyse
	pop	esi
	jmp	Analyse

cJmpn:	pop	eax
	Call	AddJump
	lodsw
	lodsd
	push	esi
	add	esi,eax
	Call	Analyse
	pop	esi
	jmp	Analyse

aJmpn:	pop	eax
	Call	AddJump
	lodsb
	lodsd
	add	esi,eax
	jmp	Analyse

aCalln:	pop	eax
	Call	AddJump
	lodsb
	lodsd
	push	esi
	add	esi,eax
	Call	Analyse
	pop	esi
	jmp	Analyse
