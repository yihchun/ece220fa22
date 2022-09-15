.ORIG x3000

LEA R6, STACK_END
LEA R1, INORD	; the current inbound train car (address of/ptr)
LEA R2, OUTORD  ; the next expected outbound train car (address of/ptr)

LOOPTOP
	LDR R3, R1, #0	; R3 is the current inbound train car name
	NOT R3, R3
	ADD R3, R3, #1
	LDR R4, R2, #0	; R4 is the next expected outbound train car name
	BRz ALLDONE
	ADD R3, R3, R4
	BRz DO_THROUGH
	; if the stack is empty, push
	LEA R3, STACK_END
	NOT R3, R3
	ADD R3, R3, #1
	ADD R3, R3, R6
	BRz DO_PUSH
	; R0 <- top of the stack, could also directly LDR, could also make PEEK
	JSR POP
	JSR PUSH
	NOT R0, R0
	ADD R0, R0, #1
	ADD R0, R0, R4
	BRz DO_POP

DO_PUSH
	LD R0, PUSHOUT
	OUT
	LDR R0, R1, #0	; R0 is the current inbound train car name
	BRz DO_FAIL
	JSR PUSH
	ADD R1, R1, #1
	BRnzp LOOPTOP

DO_POP
	LD R0, POPOUT
	OUT
	JSR POP
	ADD R2, R2, #1
	BRnzp LOOPTOP

DO_THROUGH
	LD R0, THROUGHOUT
	OUT
	ADD R1, R1, #1
	ADD R2, R2, #1
	BRnzp LOOPTOP

DO_FAIL
	LEA R0, FAILOUT
	PUTS
	HALT

ALLDONE
	HALT

INORD .STRINGZ "ABCD"  ; pointer to current (input) car in R1
OUTORD .STRINGZ "AB" ; pointer to current (expected) car in R2
THROUGHOUT .STRINGZ "T"
PUSHOUT .STRINGZ "U"
POPOUT .STRINGZ "O"
FAILOUT .STRINGZ "Sorry, I can't do that"

PUSH
	ADD R6, R6, #-1
	STR R0, R6, #0
	RET

POP
	LDR R0, R6, #0
	ADD R6, R6, #1
	RET

SOMEWHERE_ELSE .FILL x0
STACK_LIVES_HERE .BLKW #30
STACK_END .FILL xBEEF

.END