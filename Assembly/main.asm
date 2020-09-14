;$include(delay_header.asm)
extrn code(delay_1ms,delay_100ms,delay_500ms,delay_1s)

cseg at 0
	
main:
	acall delay_1ms
	mov a,#23h
	acall delay_100ms
	mov a,#23h
	acall delay_500ms
	mov a,#23h
	acall delay_1s
	mov a,#23h
		
	end