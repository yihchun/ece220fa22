.ORIG x3000

LEA R6, STACK_START

; push the values of A and B on the stack
ADD R6, R6, #-2
LEA R0, MAIN_A
LEA R1, MAIN_B
STR R0, R6, #0
STR R1, R6, #1
JSR SWAP
ADD R6, R6, #3

HALT

SWAP
ADD R6, R6, #-4
STR R5, R6, #1
ADD R5, R6, #0
STR R7, R5, #2

; tmp = *a
LDR R0, R5, #4 ; R0 <- value of a, address of the thing we want to swap
LDR R0, R0, #0 ; R0 <- *a
STR R0, R5, #0 ; tmp
; *a = *b
LDR R0, R5, #5 ; R0 <- value of b, address of the thing we want to swap
LDR R0, R0, #0 ; R0 <- *b
LDR R1, R5, #4 ; R1 <- value of a, address of the place we want to store
STR R0, R1, #0 ; *a <- R0
; *b = tmp
LDR R0, R5, #0 ; tmp
LDR R1, R5, #5 ; R1 <- value of b, address of the place we want to store
STR R0, R1, #0 ; *b <- R0

ADD R6, R5, #3
LDR R7, R5, #2
LDR R5, R5, #1
RET

STACK_SPACE .BLKW #20
STACK_START 
.BLKW #5
MAIN_A .FILL #1
MAIN_B .FILL #2

; symbol table
; tmp R5+0
; a   R5+4
; b   R5+5


.END	
