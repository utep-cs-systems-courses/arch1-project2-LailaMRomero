			.data			;
switch_state_changed:
			.word 1			;

	.text			;
jt:
	.word default		;
	.word case1				;
	.word case2				;
	.word case3				;
	.word case4				;

	.global state_advance	;
state_advance:
	cmp #4, & swicth_state_changed ;
	jnc default		       ;
	mov &switch_state_changed, r12 ;
	add r12, r12
	mov jt(r12), r0

case1:	call #toggle_red
	jmp end

case2:	call #toggle_green
	jmp end

case3:	call #toggle_red
	call #toggle_green
	jmp end

case4:	jmp end

default:

end:	pop r0
