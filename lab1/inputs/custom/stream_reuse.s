main:
        li      $3,131072             # 0x20000        #,
        ori     $3,$3,0x2010       #,,
        subu    $sp,$sp,$3       #,,
        addiu   $10,$sp,8      # tmp277,,
        li      $8,131072             # 0x20000        # tmp250,
        addu    $8,$10,$8        # ivtmp.42, tmp277, tmp250
        move    $3,$8    # ivtmp.42, ivtmp.42
        move    $2,$0    # i,
        li      $4,2048           # 0x800  # tmp289,
$L2:
        sw      $2,0($3)     # i, MEM[base: _46, offset: 0B]
        addiu   $2,$2,1        # i, i,
        addiu   $3,$3,4        # ivtmp.42, ivtmp.42,
        bne     $2,$4,$L2
        nop
        move    $3,$10   # ivtmp.35, tmp277
        move    $2,$0    # i,
        li      $4,32768                    # 0x8000         # tmp288,
$L3:
        sw      $2,0($3)     # i, MEM[base: _26, offset: 0B]
        addiu   $2,$2,1        # i, i,
        addiu   $3,$3,4        # ivtmp.35, ivtmp.35,
        bne     $2,$4,$L3
        nop
        li      $2,131072             # 0x20000        # tmp253,
        addu    $2,$10,$2        # tmp254, tmp277, tmp253
        move    $4,$2    # tmp286, tmp254
        sw      $0,8192($2)  #, sum
        li      $9,20                 # 0x14   # D.1644,
        addiu   $6,$2,8192     # D.1647, tmp286,
$L4:
        li      $7,5                        # 0x5    # D.1644,
$L9:
        move    $2,$8    # ivtmp.20, ivtmp.42
$L5:
        lw      $3,8192($4)  # D.1645, sum
        lw      $5,0($2)     # MEM[base: _32, offset: 0B], MEM[base: _32, offset: 0B]
        addiu   $2,$2,4        # ivtmp.20, ivtmp.20,
        addu    $3,$3,$5         # D.1645, D.1645, MEM[base: _32, offset: 0B]
        sw      $3,8192($4)  # D.1645, sum
        bne     $6,$2,$L5
        nop
        addiu   $7,$7,-1       # D.1644, D.1644,
        bne     $7,$0,$L9
        nop
        move    $2,$10   # ivtmp.12, tmp277
$L7:
        lw      $3,8192($4)  # D.1645, sum
        lw      $5,0($2)     # MEM[base: _33, offset: 0B], MEM[base: _33, offset: 0B]
        addiu   $2,$2,4        # ivtmp.12, ivtmp.12,
        addu    $3,$3,$5         # D.1645, D.1645, MEM[base: _33, offset: 0B]
        sw      $3,8192($4)  # D.1645, sum
        bne     $4,$2,$L7
        nop
        addiu   $9,$9,-1       # D.1644, D.1644,
        bne     $9,$0,$L4
        nop
        li      $8,131072             # 0x20000        #,
        ori     $8,$8,0x2010       #,,
        move    $2,$0    #,
        addu    $sp,$sp,$8       #,,
	li      $v0, 10       # Syscall code 10 is for exit
	syscall              # Execute the syscall