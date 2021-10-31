.text
.global _start
.extern printf
_start:
    ADR X2, cwid
    MOV X4, #0 
    MOV X5, #0 
Loop: LDR x3, [X2, X4] 
    ADD X4, X4, #8 
    ADD X5, X5, X3 
    SUB X6, x4, #64
    CMP X6, #0 
    BEQ Exit
    BL Loop
Exit:
function4:
    LDR X0, =msg
    MOV X1, X5
    BL printf

    // Exit Sequence
    MOV X0, #0
    MOV W8, #93
    SVC #0

.data
    cwid: .quad 1, 0, 4, 6, 3, 6, 7, 5
    msg: .ascii "Sum = %d\n\0"

.end
