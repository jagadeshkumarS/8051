cseg at 0
	mov r0,#00h
	rep:
	inc r0
	cjne r0,#0E1h,rep
	end