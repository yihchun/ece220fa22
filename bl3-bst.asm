.ORIG x3000

LEA R6, INIT_STACK
JSR SEARCH
HALT

SEARCH
	; callee setup
	ADD R6, R6, #-3  ; -3 = -(3+LV)
	STR R7, R6, #1   ; 1 = 1+LV
	STR R5, R6, #0   ; 0 = LV
	ADD R5, R6, #-1  ; LV-1

	; if (!root) return root;
	LDR R0, R5, #4 ; R0 <- root
	BRz SEARCH_RETURN_R0

	; if (root->data == data) return root
	LDR R1, R0, #0 ; R1 <- root->data
	LDR R2, R5, #5 ; R2 <- data
	NOT R2, R2
	ADD R2, R2, #1
	ADD R3, R1, R2 ; R3 <- root->data - data
	BRz SEARCH_RETURN_R0

	; R0 <- &(root->data)
	; p - left n - right
	BRp #1
	ADD R0, R0, #1 ; R0 <- &(root->left)
	
	LDR R1, R5, #5 ; R1 <- data
	ADD R6, R6, #-2
	STR R1, R6, #1
	LDR R0, R0, #1  ; R0 <- root->left if going left, root->right otherwise
	STR R0, R6, #0
	JSR SEARCH
	LDR R0, R6, #0
	ADD R6, R6, #3

SEARCH_RETURN_R0
	STR R0, R5, #3
	
	ADD R6, R5, #3
	LDR R7, R5, #2
	LDR R5, R5, #1
	RET
	
; <- R5
; r5 save  <- R6
; r7 save
; return value
; root
; data

STACK_START_ADDR .FILL x5000
ROOT_PTR .FILL ROOT_NODE
ROOT_NODE .FILL 5
          .FILL LEFT_CHILD
	  .FILL RIGHT_CHILD
LEFT_CHILD .FILL 3
	   .FILL x0
	   .FILL x0
RIGHT_CHILD .FILL 8
	   .FILL x0
	   .FILL x0
HEAP_POINTER .FILL HEAP_START
HEAP_START .FILL x0
STACK .BLKW #40
INIT_STACK .FILL ROOT_NODE
 .FILL 8

	
.END
	
