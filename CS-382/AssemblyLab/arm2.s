.text 
.global _start 
.extern printf
_start:
    ADR X0, msg
    LDR X20, a  
    LDR X21, b
    LDR X22, c
    /* X10 = X20 + X21 */
    ADD X10, X20, X21
    /* X10 = X10 - 14 */ 
    SUB X10, X10, #14
    CBNZ X10, Else
    ADD X22, X22, #3 
    B Exit
Else: 
    SUB X22, X22, #2
Exit:
    MOV X1, X22
    BL printf

    // Exit Sequence
    MOV X0, #0
    MOV X8, #93
    SVC #0
    
.data 
    a: .quad 7 
    b: .quad 7 
    c: .quad 0
    msg: .ascii "%d\n\0"

.end 
