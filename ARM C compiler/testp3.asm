ADDI x0, x0, #13
fib:
ADDI x9, x0, #1
LSL x9, x9, #3
SUB sp, sp, x9

ADDI x10, xzr, #2
STUR xzr, [sp, #0]
ADDI x11, xzr, #1
STUR x11, [sp, #8]

loop:
SUBS xzr, x10, x0
B.GT endl
SUBI x12, x10, #2
LSL x12, x12, #3
ADD x12, sp, x12
LDUR x13 [x12, #0]
LDUR x14 [x12, #8]
ADD x14, x13, x14
STUR x14, [x12, #16]
ADDI x10, x10, #1
B loop

endl:
ADD sp, sp, x9
BR x30

.data[60060]