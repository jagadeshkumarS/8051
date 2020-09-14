extrn code(delay_1ms,delay_100ms,delay_500ms,delay_1s)
	main:
	clr p1.0
	acall delay_500ms
	setb p1.0
	acall delay_500ms
	sjmp main
	end