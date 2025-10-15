main:
        li      $3,524288             # 0x80000        #,
        ori     $3,$3,0x10         #,,
        subu    $sp,$sp,$3       #,,
        addiu   $4,$sp,8       # tmp261,,
        li      $7,2147418112                 # 0x7fff0000     # tmp265,
        move    $6,$4    # ivtmp.17, tmp261
        move    $5,$0    # i,
        li      $3,7919           # 0x1eef         # random_seed,
        li      $9,48271                    # 0xbc8f         # tmp264,
        ori     $7,$7,0xffff       # tmp266, tmp265,
        li      $8,65536                    # 0x10000        # tmp267,
$L2:
        mul     $3,$3,$9   # D.1613, random_seed, tmp264
        sw      $5,0($6)     # i, MEM[base: _6, offset: 0B]
        andi    $2,$3,0xffff     # random_index, D.1613,
        sll     $2,$2,3    # tmp246, random_index,
        addu    $2,$4,$2         # D.1615, tmp261, tmp246
        addiu   $5,$5,1        # i, i,
        sw      $2,4($6)     # D.1615, MEM[base: _6, offset: 4B]
        and     $3,$3,$7   # random_seed, D.1613, tmp266
        addiu   $6,$6,8        # ivtmp.17, ivtmp.17,
        bne     $5,$8,$L2
        nop
        li      $3,524288             # 0x80000        # tmp249,
        addu    $3,$4,$3         # tmp250, tmp261, tmp249
        move    $2,$4    # current, tmp261
        sw      $0,0($3)     #, sum
        li      $5,10000                    # 0x2710         # D.1616,
        move    $4,$3    # tmp263, tmp250
$L3:
        lw      $3,0($4)     # D.1613, sum
        lw      $6,0($2)     # current_33->value, current_33->value
        addiu   $5,$5,-1       # D.1616, D.1616,
        addu    $3,$3,$6         # D.1613, D.1613, current_33->value
        sw      $3,0($4)     # D.1613, sum
        lw      $2,4($2)     # current, current_33->next
        bne     $5,$0,$L3
        nop
        li      $8,524288             # 0x80000        #,
        ori     $8,$8,0x10         #,,
        move    $2,$0    #,
        addu    $sp,$sp,$8       #,,
	li      $v0, 10       # Syscall code 10 is for exit
	syscall              # Execute the syscall