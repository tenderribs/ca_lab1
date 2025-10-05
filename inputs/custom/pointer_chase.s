# Random memory access pattern (pointer chasing)
# This will cause high cache miss rates due to unpredictable access patterns

.text
    # Initialize memory with a linked list of random pointers
    lui $s0, 0x1000      # Base memory address: 0x10000000
    li $s1, 16384        # Number of nodes (16K nodes)
    li $s2, 7919         # Prime number for our PRNG
    
    # Initialize all nodes with both value and next pointers
    li $t0, 0            # Loop counter
init_loop:
    # Calculate current node address: base + (i * 8)
    sll $t1, $t0, 3      # Multiply by 8 (each node is 8 bytes)
    addu $t1, $t1, $s0   # Address of current node
    
    # Store node index as the value
    sw $t0, 0($t1)
    
    # Generate pseudo-random next pointer using LCG
    mul $s2, $s2, 16807  # LCG multiplier (7^5)
    addu $s2, $s2, 13    # LCG increment
    andi $s2, $s2, 0x7FFFFFFF  # Apply modulus operation 2^31-1
    
    # Next pointer = random value % array_size
    divu $s2, $s1
    mfhi $t2             # Get remainder (random index)
    
    # Convert to address: base + (random_index * 8)
    sll $t2, $t2, 3      # Convert index to offset
    addu $t2, $t2, $s0   # Address of random node
    
    # Store the next pointer
    sw $t2, 4($t1)
    
    # Increment and continue until all nodes initialized
    addiu $t0, $t0, 1
    bne $t0, $s1, init_loop

    # Now chase pointers through memory randomly
    li $s3, 0            # Accumulator for sum
    li $s4, 100000       # Number of pointer jumps to perform
    
    # Start at first node
    move $t0, $s0        # Current pointer

chase_loop:
    # Load value and add to accumulator
    lw $t1, 0($t0)
    addu $s3, $s3, $t1
    
    # Follow the next pointer
    lw $t0, 4($t0)       # t0 = next pointer
    
    # Decrement counter and continue
    addiu $s4, $s4, -1
    bnez $s4, chase_loop
    
    # Store final result in memory
    sw $s3, 0($s0)
    
    # Exit program
    li $v0, 10
    syscall