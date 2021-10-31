.text
.global _start
.extern printf
_start:
    ADR X0, msg
    MOV X10, #1
    MOV X11, #1
    MOv x12, #0
Loop: SUB X14, X11, #10
    CMP X14, #0
    BEQ Exit
    ADD X11, X11, #1
    ADD X12, X11, #0
    ADD X10, X10, X12
    BL Loop
Exit:
function3:
    LDR X0, =msg
    MOV X1, X10
    BL printf

    // Exit Sequence
    MOV X0, #0
    MOV W8, #93
    SVC #0

.data
    msg: .ascii "Total = %d\n\0"

.end
