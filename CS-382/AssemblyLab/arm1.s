.text 
.global _start 
.extern printf
_start:
    ADR X0, msg
    LDR X20, i  
    LDR X21, f
    LDR X22, g
    SUB X9, X20, #4
    CBNZ X9, Else
    ADD X21, X22, #1 
    B Exit
Else: 
    SUB X21, X22, #2
Exit:
    MOV X1, X21
    BL printf
    
    // Exit Sequence
    MOV X0, #0
    MOV X8, #93
    SVC #0
    
.data 
    i: .quad 4 
    f: .quad 5 
    g: .quad 6
    msg: .ascii "%d\n\0"

.end 
