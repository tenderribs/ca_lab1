# compiled with https://godbolt.org, https://stackoverflow.com/a/63386888
# Step 1 compile C to ASM: mips gcc 15.2.0 with flags -xc -O3 -march=mips32 -Wall -fverbose-asm -fno-delayed-branch
# Step 2 modify assembly: 1: add .text with j main, 2. replace j $31 with syscall
# Step 3: Assemble to Hex machine code using MARS simulator

.text
	j main
main:
        li      $3,131072             # 0x20000        #,
        ori     $3,$3,0x10         #,,
        subu    $sp,$sp,$3       #,,
        addiu   $4,$sp,8       # tmp229,,
        li      $7,2147418112                 # 0x7fff0000     # tmp212,
        move    $6,$4    # ivtmp.18, tmp229
        move    $5,$0    # i,
        li      $3,7919           # 0x1eef         # random_seed,
        li      $9,16807                    # 0x41a7         # tmp210,
        ori     $7,$7,0xffff       # tmp211, tmp212,
        li      $8,16384                    # 0x4000         # tmp216,
$L2:
        mul     $3,$3,$9   # _2, random_seed, tmp210
        sw      $5,0($6)     # i, MEM[(unsigned int *)_10]
        addiu   $6,$6,8        # ivtmp.18, ivtmp.18,
        addiu   $5,$5,1        # i, i,
        andi    $2,$3,0x3fff     # _15, _2,
        sll     $2,$2,3    # _36, _15,
        addu    $2,$4,$2         # _3, tmp229, _36
        sw      $2,-4($6)    # _3, MEM[(struct Node * *)_10 + 4B]
        and     $3,$3,$7   # random_seed, _2, tmp211
        bne     $5,$8,$L2
        nop
        li      $5,131072             # 0x20000        # tmp217,
        addu    $6,$4,$5         # tmp218, tmp229, tmp217
        move    $2,$4    # current, tmp229
        addiu   $5,$5,-31072   # ivtmp_28, tmp217,
        sw      $0,0($6)     #, sum
$L3:
        lw      $3,0($6)             # sum.2_5, sum
        lw      $4,0($2)             # current_33->value, current_33->value
        addiu   $5,$5,-1       # ivtmp_28, ivtmp_28,
        addu    $3,$3,$4         # _6, sum.2_5, current_33->value
        lw      $2,4($2)             # current, current_33->next
        sw      $3,0($6)     # _6, sum
        bne     $5,$0,$L3
        nop
        li      $8,131072             # 0x20000        #,
        ori     $8,$8,0x10         #,,
        move    $2,$0    #,
        addu    $sp,$sp,$8       #,,
	li      $v0, 10       # Syscall code 10 is for exit
	syscall              # Execute the syscall