.ORIG x3000

LD R6, INIT_STACK

LEA R0, X  ; R0 <- &x
; x.func()
LDR R1, R0, #0 ; R1 <- pointer to x's vft
LDR R1, R1, #0 ; R1 <- address of the first function in x's vft
ADD R6, R6, #-1
STR R0, R6, #0
JSRR R1
HALT

X .FILL BAZ_VFT

FOO_FUNC
	ADD R6, R6, #-1
	STR R7, R6, #0
	LEA R0, FOO_STATEMENT
	PUTS
	LDR R7, R6, #0
	RET
BAR_FUNC
	ADD R6, R6, #-1
	STR R7, R6, #0
	LEA R0, BAR_STATEMENT
	PUTS
	LDR R7, R6, #0
	RET
BAZ_FUNC
	ADD R6, R6, #-1
	STR R7, R6, #0
	LEA R0, BAZ_STATEMENT
	PUTS
	LDR R7, R6, #0
	RET

FOO_STATEMENT .STRINGZ "I'm a foo\n"
BAR_STATEMENT .STRINGZ "I'm a bar\n"
BAZ_STATEMENT .STRINGZ "I'm a baz\n"

FOO_VFT .FILL FOO_FUNC
BAR_VFT .FILL BAR_FUNC
BAZ_VFT .FILL BAZ_FUNC

INIT_STACK .FILL x4000

.END