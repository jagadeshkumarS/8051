cseg at 0050h
delay_1ms:
	mov r0,#241
	djnz r0,$
	djnz r0,$
	nop
	ret

delay_100ms:
	mov r1,#99
	rep100:
	acall delay_1ms
	djnz r1,rep100
	mov r0,#142
	djnz r0,$
	djnz r0,$
	ret
	
delay_500ms:
	acall delay_100ms
	acall delay_100ms
	acall delay_100ms
	acall delay_100ms
	mov r3,#99
	rep11:
	acall delay_1ms
	djnz r3,rep11
	mov r1,#142
	djnz r1,$
	djnz r1,$
	ret
	
delay_1s:
	acall delay_500ms
	acall delay_100ms
	acall delay_100ms
	acall delay_100ms
	acall delay_100ms
	mov r1,#99
	rep1s:
	acall delay_1ms
	djnz r1,rep1s
	mov r0,#142
	djnz r0,$
	djnz r0,$
	ret	
	
	public delay_1ms,delay_100ms,delay_500ms,delay_1s
	
	end