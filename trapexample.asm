.ORIG x3000

;LD R0, TARGET_TRAP
;LEA R1, LOGICAL_RIGHT_SHIFT
;STR R1, R0, #0

AND R0, R0, #0
ADD R1, R0, #15
ADD R0, R0, #-1
;TRAP x30
JSR LOGICAL_RIGHT_SHIFT
HALT

TARGET_TRAP .FILL x30

; after this runs, TRAP x30 will take R0 <- R0 >> R1 (logical -- zero extended)
; R0 is the initial value
; R1 is the shift amount
; result is (unsigned) R0 / 2**R1
; example: R0 = 5, R1 = 1, the result is 2
; example: R0 = -1, R1 = 15, the result is 1
; R2 -- 1<<R1 (2**R1)
; R3 -- 1
; R4 -- store the result here
; loop: checks if R0 & R2 is non-zero, if so, add R3 to R4; double R2, R3
; PRE: R1 is (signed and) non-negative
; POST: R1 is overwritten 
LOGICAL_RIGHT_SHIFT
	; save registers
	ST R2, OLD_R2
	ST R3, OLD_R3
	ST R4, OLD_R4
	; set up R2
	AND R4, R4, #0
	ADD R2, R4, #1
	ADD R3, R2, #0

	ADD R1, R1, #0
	BRnz MAIN_LOOP
R2_LOOP
	ADD R2, R2, R2
	ADD R1, R1, #-1
	BRp R2_LOOP

MAIN_LOOP
	AND R1, R0, R2
	BRz #1
	ADD R4, R4, R3
	ADD R3, R3, R3
	ADD R2, R2, R2
	BRnp MAIN_LOOP

	ADD R0, R4, #0
	; restore registers
	LD R2, OLD_R2
	LD R3, OLD_R3
	LD R4, OLD_R4
	JMP R7

OLD_R2 .FILL #0
OLD_R3 .FILL #0
OLD_R4 .FILL #0
.BLKW #3
.FILL #-1

.END