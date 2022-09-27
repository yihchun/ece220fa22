.ORIG x3000

LEA R6, STACK_START
JSR FACTORIAL
HALT

FACTORIAL
ADD R6, R6, #-5
STR R5, R6, #2
ADD R5, R6, #1
STR R7, R5, #2

AND R0, R0, #0   ; accum=1
ADD R0, R0, #1
STR R0, R5, #0

;for (i=1; i<=n; i++)
AND R0, R0, #0   ; i=1
ADD R0, R0, #1
STR R0, R5, #-1
FORLOOP
LDR R0, R5, #-1
LDR R1, R5, #4
NOT R1, R1
ADD R1, R1, #1
ADD R2, R0, R1 ; R2 <- i-n
BRp DONEWITHFOR
; accum = multiply(accum, i)
LDR R0, R5, #0  ; R0 <- accum
LDR R1, R5, #-1 ; R1 <- i
ADD R6, R6, #-2
STR R1, R6, #1
STR R0, R6, #0
JSR MULTIPLY
LDR R0, R6, #0 ; return value
STR R0, R5, #0
ADD R6, R6, #3
; i++
LDR R0, R5, #-1
ADD R0, R0, #1
STR R0, R5, #-1
BRnzp FORLOOP

DONEWITHFOR
; return accum
LDR R0, R5, #0
STR R0, R5, #3

ADD R6, R5, #3
LDR R7, R5, #2
LDR R5, R5, #1
RET

; Symbol Table for factorial
; i     R5-1
; accum R5+0
; n     R5+4


MULTIPLY
ADD R6, R6, #-4
STR R5, R6, #1
ADD R5, R6, #0
STR R7, R5, #2

; tmp = a*b
LDR R0, R5, #4 ; R0 <- a
LDR R1, R5, #5 ; R1 <- b
AND R2, R2, #0 ; accumulator, later send this to tmp
ADD R3, R2, #1

MULLOOPTOP
AND R4, R1, R3
BRz NOADD
ADD R2, R0, R2
NOADD
ADD R3, R3, R3
ADD R0, R0, R0
BRnp MULLOOPTOP

STR R2, R5, #0 ; tmp <- accumulator
STR R2, R5, #3 ; return tmp
ADD R6, R5, #3
LDR R7, R5, #2
LDR R5, R5, #1
RET

; Symbol Table for Multiply
; tmp  R5 +0
; a    R5 +4
; b    R5 +5




STACK_SPACE .BLKW #60
STACK_START .FILL #5
.FILL #4

.END