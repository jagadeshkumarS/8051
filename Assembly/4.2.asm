cseg at 0
	mov 20h,#05h
	mov r0,#20h
	rep:
	inc 20h
	cjne @r0,#55h,rep
	end