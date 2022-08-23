.ORIG x3000

; R1: address of current character
; R2: current character
; R3: value of the bin we're incrementing
; R4: base of the histogram table
LEA R1, TARGET_STRING
LEA R4, HIST_TABLE

TOP_OF_LOOP
; load the current character into R2
LDR R2, R1, #0

; split based on type
BRz DONE
; looking for upper-case characters
ADD R2, R2, #-16
ADD R2, R2, #-16
ADD R2, R2, #-16
ADD R2, R2, #-16
BRnz NON_ALPHA
ADD R5, R2, #-13
ADD R5, R5, #-13
BRnz HANDLE_UPPER
ADD R2, R5, #-6
BRnz NON_ALPHA
ADD R5, R2, #-13
ADD R5, R5, #-13
BRnz HANDLE_LOWER

NON_ALPHA
	LDR R3, R4, #0   ; R3 <- M[R4]
	ADD R3, R3, #1   ; R3 <- R3+1
	STR R3, R4, #0   ; M[R4] <- R3
	BRnzp NEXT_CHAR

HANDLE_UPPER
	ADD R2, R4, R2
	LDR R3, R2, #0
	ADD R3, R3, #1   ; R3 <- R3+1
	STR R3, R2, #0

NEXT_CHAR

DONE
	HALT

; one spot for non-alphabetical characters, 26 spots for a-z respectively
HIST_TABLE .BLKW #27
TARGET_STRING .STRINGZ "The quick brown fox jumps over the lazy dog."

.END
