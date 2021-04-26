ADDI x0, x0, #2
ADDI x1, x1, #10

power: 
CBNZ x1, l1
ADDI x2, xzr, #1
BR x30

l1: 
SUBI sp, sp, #16
STUR x19, [sp, #8]
STUR x30, [sp, #0]

ANDI x19, x1, #1
LSR x1, x1, #1
BL power
MUL x2, x2, x2
CBZ x19, l2
MUL x2, x0, x2

l2: 
LDUR x30, [sp, #0]
LDUR x19, [sp, #8]
ADDI sp, sp, #16
BR x30


.data[60060]
1


