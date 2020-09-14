mov b,#0aah
mov a,b
mov r0,#08h
rep:
rrc a
jnc next
inc r5
next:
djnz r0,rep
end