ADDI x0, x0, #4

fact: SUBI sp, sp, #16
STUR lr, [sp, #8]
STUR x0, [sp, #0]
SUBIS xzr, x0, #1
B.GE l1
ADDI x1, xzr, #1
ADDI sp, sp, #16
BR lr

l1: SUBI x0, x0, #1
BL fact
LDUR x0, [sp, #0]
LDUR lr, [sp, #8]
ADDI sp, sp, #16
MUL x1, x0, x1
BR lr


.data[60060]
0