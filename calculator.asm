.ORIG x3000
LEA R6, STACK_END	; Initializes stack ptr to space we allocate below

LOOPTOP			; loop that takes input
	GETC		; take input
	OUT		; echo back
	ADD R1, R0, #-16 ; subtract x30 to map '0' -> 0 and '9' to 9 in R1
	ADD R1, R1, #-16
	ADD R1, R1, #-16
	BRn NOT_A_NUMBER ; the value was less than '0', might be an op
	ADD R2, R1, #-9	 ; check if the value is between '0' and '9'
	    	    	 ; already know >= '0'
	BRp LOOPTOP	 ; exceeds '9', no operators live there, so next char
	ADD R0, R1, #0	 ; moving R1->R0 to push the digit onto the stack
	JSR PUSH    	 ; perform the push
	BRnzp LOOPTOP	 ; done with this character, get next one
NOT_A_NUMBER  		 ; not a digit, but maybe an op
	ADD R1, R1, #5	 ; if R0 == '+', then R1 == -5
	BRz DO_ADD  	 ; == '+'
	ADD R1, R1, #1	 ; if R0 == '*', then R1 was -6, now -1
	BRz DO_MULTIPLY	 ; == '*'
	BRnzp LOOPTOP	 ; not a recognized operator, get next character

DO_ADD
	JSR STACK_ADD
	BRnzp LOOPTOP

DO_MULTIPLY
	JSR STACK_MULT
	BRnzp LOOPTOP

STACK_ADD
	ST R7, SOMEWHERE_ELSE		; our JSRs will clobber R7, better save
	       				; it (somewhere else)
	JSR POP				; call pop to get the first operand
	ADD R1, R0, #0   ; R1 <- R0	; move the first operand to R1
	JSR POP	    	      	 	; call pop to get the second operand
	ADD R0, R0, R1			; perform + operation on R0, R1
	JSR PUSH    			; push the result onto the stack
	LD R7, SOMEWHERE_ELSE		; Restore R7 so RET is not infinite loop
	RET    				; go back to the function that called us

STACK_MULT
	ST R7, SOMEWHERE_ELSE		; our JSRs will clobber R7, better save
	       				; it (somewhere else)
	JSR POP				; call pop to get the first operand
	ADD R1, R0, #0   ; R1 <- R0	; move the first operand to R1
	JSR POP	    	      	 	; call pop to get the second operand
	    				; R0 <- R0 * R1
	AND R3, R3, #0
MULTLOOP
	ADD R3, R0, R3
	ADD R1, R1, #-1
	BRnp MULTLOOP
	ADD R0, R3, #0
	JSR PUSH    			; push the result onto the stack
	LD R7, SOMEWHERE_ELSE		; Restore R7 so RET is not infinite loop
	RET    				; go back to the function that called us	
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
