.text 
.global _start
.extern printf
// Jack Harrington 
// I pledge my honor that I have abided by the Stevens Honor System.
_start:
    ADR X19, i
    MOV X0, #4
    BL findMax
    BL else
    BL exit

findMax: // findMax function
    SUB SP, SP, #16 
    STUR X30, [SP, #8]
    STUR X0, [SP, #0]
    CMP X0, #1
    B.GT firstLoop // Compares X0 X1
    LDUR X1, [X19, #0]
    ADD SP, SP, #16 // Move two values in stack
    BR LR

firstLoop: // Iterates through stacks and does comparisons
    SUB X0, X0, #1
    BL findMax
    LDUR X0, [SP, #0]
    LDUR X30, [SP, #8]
    ADD SP, SP, #16
    ADD X19, X19, #8
    LDR X6, [X19] // Holds the value of A[n-1]
    CMP X6, X1
    B.GT secondLoop
    BR X30

secondLoop: // Stores new value of A[n-1] in X1
    MOV X1, X6
    BR X30

else: 
    ADR X0, msg 
    BL printf

exit:
    // Exit Sequence
    MOV X0, #0
    MOV X8, #93
    SVC #0

.data
    i: .dword 2, 9, 8, 1
    msg: .ascii "MAX = %d\n\0"

.end
