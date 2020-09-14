cseg at 0
	jnc zero
	jnb ov,zero
	mov r7,#01h
	sjmp last
	zero:
	mov r7,#00h
	last:

;	mov acc.0,c
;	mov c,0d0h.2
;	mov acc.1,c
;	mov c,acc.0
;	cjne a,#03,one
;	mov r7,#01h
;	sjmp last
;	one:
;	mov r7,#00h
;	last:
;	clr a
	end