.ORIG x3000

LEA R6, STACK_START
JSR SUMTON
HALT

SUMTON
	ADD R6, R6, #-4
	STR R5, R6, #1
	ADD R5, R6, #0
	STR R7, R5, #2

	; symbol table
	; n   param sumton R5+4
	; tmp l.v.  sumton R5+0

	; if (n <= 1) return n;
	LDR R0, R5, #4
	ADD R1, R0, #1
	BRnz RETURN_R0

	; tmp = sumton(n-1)
	ADD R6, R6, #-1
	LDR R0, R5, #4
	ADD R0, R0, #-1
	STR R0, R6, #0
	JSR SUMTON
	LDR R0, R6, #0
	STR R0, R5, #0
	ADD R6, R6, #2

	LDR R0, R5, #0 ;tmp
	LDR R1, R5, #4 ;n
	ADD R0, R0, R1 ;R0 <- tmp+n
RETURN_R0
	STR R0, R5, #3
	ADD R6, R5, #3
	LDR R7, R5, #2
	LDR R5, R5, #1
	RET



RTSTACK .BLKW #30
STACK_START .FILL x4