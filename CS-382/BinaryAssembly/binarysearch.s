/***********************************************************************************************
* Name          : BinarySearch.s
* Author        : Jack Harrington
* Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
* Date          : October 31, 2021
* Descritption  : Implementation of selection sort in assembly.
***********************************************************************************************/

.text
.global _start
.extern printf

_start:
    // Takes user input from terminal.
    LDR X0, =scan
    LDR X1, =query
    BL scanf
    ADR X19, arr
    ADR X20, size
    LDUR x1, [X20, 0] // Size of the array.
    MOV x2, 0 // Iterator
    BL SelectionSort
    BL printLoop
    BL BinarySearch
    B EXIT

// Computes the swap of array[i] elements
Swaps: //x7 has new address of min
    LDUR x8, [x7,0] //new min
    LDR x9, [X19, x3]
    STUR x9, [x7, 0]
    STR x8, [X19, x3]
    BR x30

// Utilized to calculate the min value of Array[i].
Min:
    CMP X3, X6
    BEQ exitMin
    LDR x4, [x7, 0]
    ADD x3, x3, 8
    // Gets the value of i + 1
    LDR x5, [X19, x3]
    CMP X5, X4
    BLT newMin
    B Min

// Selection Sort Algorithm.
SelectionSort:
    SUB SP, SP, 8
    STUR X30, [SP, 0]
    // Gets final element in the array.
    LSL X6, x1, 3 
// Actual sorting 
SortLoop: 
    CMP x2, x1
    BEQ Exit
    LSL X3, X2, 3
    // Value to be swapped.
    LDR X4, [X19, X3]
    ADD x7, x19, x3 
    // Branches to get min.
    BL Min 
    LSL X3, X2, 3
    // Preforms swaps on elements of array.
    BL Swaps
    ADD x2, X2, 1
    // Repeats
    B SortLoop
// Exit call.
Exit:
    LDUR X30, [SP, 0]
    ADD SP, SP, 8
    BR X30

// Gets the new lowest value in array[i].
newMin:
    ADD x7, X19, x3
    B Min
// Exit Call.
exitMin:
    BR x30

// Called on the sorted array to print results in given format.
printLoop:
    MOV X20, x1
    MOV X21, 0
printsLoop:
    LSL x10, X21, 3
    LDR x1, [X19, x10]
    ADR x0, str
    SUB SP, SP, 8
    STUR X30, [SP, #0]
    BL printf
    LDUR X30, [SP, #0]
    ADD SP, SP, #8
    ADD X21, X21, 1
    CMP X21, X20
    BEQ ExitPrint 
    B printsLoop
// Exit call.
ExitPrint:
    // End Program.
    BR X30

BinarySearch:
    // Searches the Array[i] for a given value from user.
    ADR x22, arr
    MOV x10, 0 
    MOV x12, #7 
    LDR x20, =query
    LDUR X20, [X20, #0]

loop:
    ADD x11, x10, #1
    CMP x11, x12
    BEQ end
    ADD x13, x10, x12          
    ASR x13, x13, #1
    MOV x18, #8
    MUL x19, x13, x18
    LDR x14, [x22,x19] 
    CMP x14, x20 
    BLE L1
    MOV x12, x13
    BL  loop


L1:
    MOV x10, x13
    BL  loop

end: 
    MOV x18, #8
    MUL x19, x10, x18
    LDR x14, [x22, x19] 
    CMP x14, x20
    BEQ If
    BL Else
If:
    LDR x0, =print_num
    MOV x1, x10
    BL printf
    BL Exit

Else:
    LDR    x0, =print_num
    MOV    x1, -1
    BL printf

EXIT:
    // Exit Sequence
    MOV X0, #0
    MOV X8, #93
    SVC #0

.data
arr:    .quad 6, 7, 4, 2, 1, 5, 9, 3 // Array values.
str:    .ascii "%ld \n\0" // Print statement.
size:   .quad 8 // Array length.
scan:   .string "%ld"
query:  .quad 0
print_num: .ascii "Target at: %d\n\0"
.end
