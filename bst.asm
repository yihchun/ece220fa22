.ORIG x3000

; setup stack initial
LD R6, STACK_START_ADDR

; make the first call
LD R1, SEARCH_FOR
LEA R0, ROOT_PTR
ADD R6, R6, #-2
STR R0, R6, #0
STR R1, R6, #1
JSR BST_INSERT
ADD R6, R6, #3

LEA R0, ROOT_PTR
LD R1, DELETE_ELT
ADD R6, R6, #-2
STR R0, R6, #0
STR R1, R6, #1
JSR BST_DELETE
HALT

SEARCH_FOR .FILL 8
DELETE_ELT .FILL 5

MALLOC
	ADD R6, R6, #-3
	STR R1, R6, #0 ; R1 save
	STR R0, R6, #1 ; R0 save
	LD R1, HEAP_POINTER
	STR R1, R6, #2
	LDR R0, R6, #3 ; malloc's parameter
	ADD R0, R0, R1
	ST R0, HEAP_POINTER
	LDR R1, R6, #0 ; R1 save
	LDR R0, R6, #1 ; R0 save
	ADD R6, R6, #2
	RET

BST_DELETE
	ADD R6, R6, #-5
	STR R5, R6, #2
	ADD R5, R6, #1
	STR R7, R5, #2

BST_DELETE_WHILETOP
	; while (*root != NULL && (*root)->val != v) {
	LDR R0, R5, #4 ; R0 <- root
	LDR R0, R0, #0 ; R0 <- *root
	BRz BST_DELETE_WHILEBOT
	LDR R1, R5, #5 ; R1 <- v
	LDR R2, R0, #0 ; R2 <- (*root)->val
	NOT R2, R2
	ADD R2, R2, #1
	ADD R2, R1, R2 ; R2 <- v-(*root)->val
	BRz BST_DELETE_WHILEBOT

	BRn #1
	ADD R0, R0, #1 ; execute only when going right
	ADD R0, R0, #1
	STR R0, R5, #4 ; root = &((*root)->[left|right]);
	BRnzp BST_DELETE_WHILETOP

BST_DELETE_WHILEBOT
	; if (!*root) return
	; can do these two LDRs instead of ADD
	;LDR R0, R5, #4 ; R0 <- root
	;LDR R0, R0, #0 ; R0 <- *root
	ADD R0, R0, #0 ; set cc
	BRz BST_DELETE_DONE

	; if ((*root)->left && (*root)->right)
	LDR R1, R0, #1 ; R1 <- (*root)->left
	BRz BST_DELETE_EASYCASE
	LDR R2, R0, #2 ; R2 <- (*root)->right
	BRz BST_DELETE_EASYCASE

	;for (walk = &((*root)->right); (*walk)->left;
	;     walk = &((*walk)->left))   ;
	; init
	ADD R1, R0, #2 ; R1 <- &(*root)->right
	STR R1, R5, #0 ; walk <- R1
BST_DELETE_FOR_TOP ; keep looping while (*walk)->left
	LDR R1, R5, #0  ; R1 <- walk
	LDR R1, R1, #0  ; R1 <- *walk
	LDR R2, R1, #1  ; R2 <- (*walk)->left
	BRz BST_DELETE_FOR_BOT
	; reinit
	ADD R1, R1, #1 ; R1 <- &((*walk)->left)
	STR R1, R5, #0 ; walk <- R1
	BRnzp BST_DELETE_FOR_TOP	

BST_DELETE_FOR_BOT
	; (*root)->val = (*walk)->val
	; *root is in R0, *walk is in R1
	LDR R2, R1, #0
	STR R2, R0, #0
	; root = walk
	LDR R2, R5, #0
	STR R2, R5, #4

BST_DELETE_EASYCASE
	; tmp = *root
	LDR R0, R5, #4 ; R0 <- root
	LDR R1, R0, #0 ; R1 <- *root
	STR R1, R5, #-1 ; tmp = *root
	ADD R2, R1, #1 ; R2 <- &((*root)->left)
	LDR R3, R1, #1 ; R3 <- (*root)->left
	BRnp #1
	ADD R2, R2, #1
	LDR R2, R2, #0 ; R2 <- (*root)->[left|right]
	STR R2, R0, #0	; *root = R2
	
BST_DELETE_DONE
	ADD R6, R5, #3
	LDR R7, R5, #2
	LDR R5, R5, #1
	RET

; tmp <- R6
; walk <- R5
; r5 save
; r7 save
; ret val +3
; root +4
; v +5

BST_INSERT
	ADD R6, R6, #-3 ; callee setup, 0 locals
	STR R5, R6, #0
	ADD R5, R6, #-1
	STR R7, R5, #2

BST_INSERT_WHILE_TOP
	LDR R0, R5, #4 ; root
	LDR R1, R0, #0 ; *root
	BRz BST_INSERT_WHILE_BOT ; if (*root) == NULL
	LDR R2, R1, #0 ; (*root)->val
	NOT R2, R2
	ADD R2, R2, #1
	LDR R3, R5, #5 ; v
	ADD R2, R2, R3 ; v-(*root)->val
	BRn #1         ; we're going left, skip +1
	ADD R1, R1, #1 ; move the *root pointer to left
	ADD R1, R1, #1 ; move the *root pointer to where we're going
	STR R1, R5, #4 ; *root = &((*root)->[left or right]);
	BRnzp BST_INSERT_WHILE_TOP

BST_INSERT_WHILE_BOT
	AND R4, R4, #0 ; caller setup to call malloc(3)
	ADD R4, R4, #3
	ADD R6, R6, #-1
	STR R4, R6, #0
	JSR MALLOC
	LDR R4, R6, #0 ; return value of malloc(3)
	ADD R6, R6, #2 ; caller teardown malloc
	STR R4, R0, #0 ; root lives in R0, so *root = R4
	LDR R1, R5, #5 ; v
	STR R1, R4, #0 ; (*root)->val = v
	AND R1, R1, #0 ; R1 <- NULL
	STR R1, R4, #1 ; (*root)->left = NULL
	STR R1, R4, #2 ; (*root)->right = NULL

	ADD R6, R5, #3 ; callee teardown
	LDR R7, R5, #2
	LDR R5, R5, #1
	RET
	
	

; symbol table for BST_SEARCH
; root R5+4
; v    R5+5



BST_SEARCH
	ADD R6, R6, #-3
	STR R5, R6, #0
	ADD R5, R6, #-1
	STR R7, R5, #2

BST_SEARCH_WHILE_TOP
	LDR R0, R5, #4 ; root
	BRz BST_SEARCH_RETURN
	LDR R1, R0, #0 ; root->val
	NOT R1, R1
	ADD R1, R1, #1
	LDR R2, R5, #5
	ADD R1, R1, R2 ; v - root->val
	BRz BST_SEARCH_RETURN
	BRn #1
	ADD R0, R0, #1
	LDR R0, R0, #1
	STR R0, R5, #4
	BRnzp BST_SEARCH_WHILE_TOP

BST_SEARCH_RETURN
	STR R0, R5, #3
	ADD R6, R5, #3
	LDR R7, R5, #2
	LDR R5, R5, #1
	RET


STACK_START_ADDR .FILL x5000
ROOT_PTR .FILL ROOT_NODE
ROOT_NODE .FILL 5
          .FILL LEFT_CHILD
	  .FILL RIGHT_CHILD
LEFT_CHILD .FILL 3
	   .FILL x0
	   .FILL x0
RIGHT_CHILD .FILL 9
	   .FILL SEVEN_CHILD
	   .FILL x0
SEVEN_CHILD .FILL 7
	    .FILL x0
	    .FILL x0
HEAP_POINTER .FILL HEAP_START
HEAP_START .FILL x0

.END
