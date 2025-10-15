.text
lui $a0, 0x1000
 li $t0, 0x12345678
 sw $t0, 0($a0)
 li $t0, 0
li $t1, 0
li $t2, 0
li $t3, 0
li $t4, 0
li $t5, 0
li $t6, 0
li $t7, 0
li $s4, 1000
main:
 subi $s4, $s4, 1
 subu   $t2 , $t3 , $t1 
 addiu   $t4 , $t4 , 3814213745 
 xori   $t3 , $t0 , 3997488569 
 lb   $t5 , 0($a0) 
 or   $t2 , $t0 , $t0 
 sw   $t7 , 0($a0) 
 ori   $t5 , $t4 , 4239107734 
 xor   $t6 , $t6 , $t6 
 sb   $t2 , 0($a0) 
 lbu   $t5 , 0($a0) 
 multu  $t3 , $t3 
 add $0, $0, $0
 mflo  $t4 
 lhu   $t3 , 0($a0) 
 nor   $t2 , $t6 , $t0 
 mult  $t4 , $t7 
 add $0, $0, $0
 mflo  $t7 
 andi   $t2 , $t5 , 1247542587 
 xori   $t7 , $t6 , 1594626888 
 ori   $t1 , $t2 , 2674524676 
 mult  $t2 , $t2 
 mult  $t7 , $t5 
 add $0, $0, $0
 mflo  $t3 
 nor   $t3 , $t4 , $t0 
 nor   $t7 , $t2 , $t5 
 sh   $t1 , 0($a0) 
 lb   $t7 , 0($a0) 
 addu   $t1 , $t5 , $t6 
 multu  $t3 , $t7 
 add $0, $0, $0
 mflo  $t3 
 and   $t4 , $t6 , $t6 
 mult  $t6 , $t4 
 add $0, $0, $0
 mflo  $t6 
 addiu   $t3 , $t6 , 1797446449 
 lw   $t7 , 0($a0) 
 ori   $t3 , $t7 , 2549865114 
 andi   $t7 , $t2 , 1606568530 
 or   $t3 , $t2 , $t1 
 xori   $t0 , $t1 , 171383535 
 multu  $t4 , $t0 
 add $0, $0, $0
 mflo  $t0 
 mult  $t1 , $t6 
 add $0, $0, $0
 mflo  $t0 
 lhu   $t6 , 0($a0) 
 andi   $t5 , $t6 , 2046525660 
 or   $t5 , $t7 , $t1 
 ori   $t0 , $t7 , 2939708916 
 and   $t3 , $t0 , $t7 
 mult  $t5 , $t0 
 mult  $t4 , $t1 
 add $0, $0, $0
 mflo  $t0 
 addiu   $t1 , $t1 , 723313085 
 lh   $t1 , 0($a0) 
 subu   $t2 , $t0 , $t6 
 mult  $t1 , $t5 
 mult  $t6 , $t5 
 add $0, $0, $0
 mflo  $t2 
 subu   $t3 , $t1 , $t7 
 xori   $t0 , $t3 , 903029912 
 mult  $t5 , $t4 
 mult  $t0 , $t1 
 add $0, $0, $0
 mflo  $t0 
 mult  $t2 , $t7 
 mult  $t2 , $t5 
 add $0, $0, $0
 mflo  $t3 
 sw   $t3 , 0($a0) 
 addiu   $t1 , $t7 , 2816221821 
 ori   $t3 , $t6 , 4215491713 
 mult  $t1 , $t5 
 add $0, $0, $0
 mflo  $t0 
 mult  $t5 , $t0 
 mult  $t0 , $t2 
 add $0, $0, $0
 mflo  $t4 
 mult  $t6 , $t6 
 add $0, $0, $0
 mflo  $t2 
 or   $t0 , $t3 , $t5 
 mult  $t4 , $t5 
 add $0, $0, $0
 mflo  $t2 
 ori   $t4 , $t3 , 2916836708 
 addiu   $t0 , $t2 , 2012814864 
 subu   $t1 , $t1 , $t5 
 addu   $t5 , $t7 , $t0 
 xor   $t5 , $t7 , $t6 
 mult  $t6 , $t5 
 add $0, $0, $0
 mflo  $t2 
 xor   $t0 , $t3 , $t4 
 lhu   $t1 , 0($a0) 
 xor   $t0 , $t7 , $t2 
 mult  $t0 , $t2 
 add $0, $0, $0
 mflo  $t1 
 sb   $t7 , 0($a0) 
 lbu   $t1 , 0($a0) 
 mult  $t2 , $t1 
 mult  $t0 , $t3 
 add $0, $0, $0
 mflo  $t5 
 mult  $t3 , $t6 
 mult  $t6 , $t0 
 add $0, $0, $0
 mflo  $t3 
 mult  $t1 , $t5 
 mult  $t0 , $t7 
 add $0, $0, $0
 mflo  $t2 
 lw   $t1 , 0($a0) 
 mult  $t6 , $t0 
 add $0, $0, $0
 mflo  $t0 
 mult  $t2 , $t0 
 mult  $t7 , $t7 
 add $0, $0, $0
 mflo  $t0 
 sw   $t0 , 0($a0) 
 andi   $t0 , $t0 , 920740911 
 lhu   $t7 , 0($a0) 
 xori   $t5 , $t6 , 3476214756 
 or   $t3 , $t2 , $t0 
 andi   $t5 , $t7 , 3420383560 
 nor   $t4 , $t4 , $t4 
 mult  $t1 , $t3 
 mult  $t4 , $t1 
 add $0, $0, $0
 mflo  $t4 
 nor   $t7 , $t1 , $t7 
 mult  $t3 , $t3 
 mult  $t3 , $t5 
 add $0, $0, $0
 mflo  $t3 
 xori   $t4 , $t4 , 1133199070 
 or   $t3 , $t6 , $t6 
 or   $t6 , $t0 , $t4 
 lbu   $t2 , 0($a0) 
 ori   $t3 , $t6 , 500064667 
 xori   $t0 , $t7 , 3714349876 
 mult  $t3 , $t0 
 mult  $t2 , $t7 
 add $0, $0, $0
 mflo  $t1 
 multu  $t0 , $t3 
 add $0, $0, $0
 mflo  $t0 
 and   $t7 , $t3 , $t3 
 or   $t4 , $t6 , $t6 
 ori   $t6 , $t4 , 1815618360 
 lhu   $t6 , 0($a0) 
 addu   $t1 , $t5 , $t6 
 mult  $t6 , $t0 
 add $0, $0, $0
 mflo  $t2 
 xori   $t0 , $t0 , 4235412934 
 nor   $t7 , $t6 , $t1 
 mult  $t6 , $t4 
 mult  $t2 , $t1 
 add $0, $0, $0
 mflo  $t7 
 xor   $t3 , $t7 , $t5 
 mult  $t7 , $t6 
 add $0, $0, $0
 mflo  $t6 
 and   $t3 , $t4 , $t3 
 sb   $t3 , 0($a0) 
 mult  $t1 , $t3 
 mult  $t2 , $t1 
 add $0, $0, $0
 mflo  $t6 
 sh   $t2 , 0($a0) 
 xori   $t5 , $t6 , 2852815076 
 sh   $t0 , 0($a0) 
 andi   $t7 , $t6 , 1030435134 
 sw   $t0 , 0($a0) 
 addiu   $t2 , $t3 , 4098563297 
 sh   $t0 , 0($a0) 
 sh   $t5 , 0($a0) 
 andi   $t0 , $t7 , 2250437082 
 xori   $t4 , $t2 , 2794361914 
 addiu   $t7 , $t5 , 3260883244 
 mult  $t7 , $t4 
 mult  $t6 , $t3 
 add $0, $0, $0
 mflo  $t3 
 multu  $t2 , $t5 
 add $0, $0, $0
 mflo  $t4 
 lb   $t7 , 0($a0) 
 addiu   $t5 , $t5 , 3362898687 
 subu   $t4 , $t4 , $t0 
 sb   $t1 , 0($a0) 
 xori   $t4 , $t6 , 2120879652 
 sh   $t3 , 0($a0) 
 multu  $t2 , $t3 
 add $0, $0, $0
 mflo  $t4 
 mult  $t6 , $t5 
 add $0, $0, $0
 mflo  $t4 
 nor   $t6 , $t6 , $t6 
 addiu   $t2 , $t2 , 4256202486 
 sb   $t2 , 0($a0) 
 ori   $t0 , $t3 , 536566404 
 addiu   $t1 , $t2 , 1890886015 
 addiu   $t1 , $t7 , 2627817669 
 subu   $t3 , $t7 , $t6 
 and   $t1 , $t5 , $t2 
 mult  $t6 , $t4 
 add $0, $0, $0
 mflo  $t1 
 mult  $t4 , $t2 
 mult  $t5 , $t5 
 add $0, $0, $0
 mflo  $t3 
 xori   $t6 , $t5 , 1802481648 
 andi   $t4 , $t1 , 3377488884 
 addiu   $t1 , $t0 , 2832662789 
 and   $t0 , $t5 , $t6 
 sb   $t0 , 0($a0) 
 mult  $t5 , $t5 
 mult  $t3 , $t7 
 add $0, $0, $0
 mflo  $t6 
 nor   $t3 , $t4 , $t5 
 mult  $t6 , $t0 
 add $0, $0, $0
 mflo  $t4 
 xori   $t0 , $t5 , 3946588878 
 multu  $t2 , $t3 
 add $0, $0, $0
 mflo  $t0 
 ori   $t1 , $t1 , 4192391165 
 multu  $t7 , $t2 
 add $0, $0, $0
 mflo  $t1 
 ori   $t7 , $t3 , 3243003128 
 xor   $t4 , $t1 , $t2 
 sb   $t5 , 0($a0) 
 mult  $t2 , $t2 
 mult  $t3 , $t4 
 add $0, $0, $0
 mflo  $t3 
 andi   $t1 , $t5 , 2828165438 
 multu  $t4 , $t1 
 add $0, $0, $0
 mflo  $t3 
 sh   $t7 , 0($a0) 
 xori   $t1 , $t6 , 2724665339 
 lhu   $t4 , 0($a0) 
 lb   $t1 , 0($a0) 
 addu   $t2 , $t6 , $t6 
 and   $t6 , $t1 , $t1 
 xori   $t5 , $t2 , 1443620898 
 xor   $t0 , $t1 , $t3 
 ori   $t3 , $t2 , 204767171 
 sw   $t2 , 0($a0) 
 andi   $t0 , $t0 , 3185280590 
 andi   $t4 , $t4 , 4246828201 
 andi   $t2 , $t0 , 3233994489 
 ori   $t4 , $t0 , 2963083890 
 mult  $t1 , $t0 
 mult  $t5 , $t6 
 add $0, $0, $0
 mflo  $t5 
 xori   $t5 , $t1 , 1301629720 
 sh   $t5 , 0($a0) 
 addu   $t7 , $t3 , $t7 
 andi   $t2 , $t4 , 3510079956 
 nor   $t7 , $t5 , $t0 
 sh   $t4 , 0($a0) 
 or   $t1 , $t1 , $t4 
 andi   $t6 , $t2 , 3781324874 
 sb   $t5 , 0($a0) 
 xori   $t3 , $t5 , 2889240158 
 xori   $t4 , $t5 , 3300013764 
 and   $t5 , $t5 , $t7 
 mult  $t7 , $t5 
 add $0, $0, $0
 mflo  $t5 
 addiu   $t1 , $t2 , 2707568830 
 andi   $t0 , $t1 , 2242638400 
 xor   $t0 , $t2 , $t6 
 mult  $t4 , $t3 
 mult  $t1 , $t1 
 add $0, $0, $0
 mflo  $t6 
 xor   $t5 , $t5 , $t0 
 mult  $t4 , $t3 
 add $0, $0, $0
 mflo  $t5 
 multu  $t7 , $t5 
 add $0, $0, $0
 mflo  $t3 
 xor   $t7 , $t2 , $t4 
 mult  $t0 , $t7 
 mult  $t4 , $t6 
 add $0, $0, $0
 mflo  $t3 
 multu  $t6 , $t3 
 add $0, $0, $0
 mflo  $t6 
 sh   $t3 , 0($a0) 
 and   $t4 , $t1 , $t3 
 xori   $t6 , $t1 , 978169217 
 addu   $t7 , $t5 , $t1 
 xori   $t4 , $t3 , 1619579933 
 addu   $t1 , $t6 , $t4 
 sb   $t6 , 0($a0) 
 sb   $t7 , 0($a0) 
 mult  $t6 , $t1 
 mult  $t2 , $t3 
 add $0, $0, $0
 mflo  $t3 
 mult  $t7 , $t2 
 mult  $t3 , $t7 
 add $0, $0, $0
 mflo  $t3 
 mult  $t0 , $t5 
 mult  $t2 , $t4 
 add $0, $0, $0
 mflo  $t5 
 mult  $t6 , $t5 
 mult  $t5 , $t3 
 add $0, $0, $0
 mflo  $t2 
 addu   $t1 , $t4 , $t0 
 or   $t6 , $t6 , $t7 
 addiu   $t7 , $t1 , 3786623667 
 nor   $t0 , $t6 , $t1 
 or   $t2 , $t1 , $t6 
 multu  $t7 , $t4 
 add $0, $0, $0
 mflo  $t0 
 lhu   $t3 , 0($a0) 
 subu   $t5 , $t7 , $t7 
 andi   $t0 , $t7 , 2572305140 
 mult  $t3 , $t0 
 add $0, $0, $0
 mflo  $t7 
 andi   $t2 , $t2 , 1685207885 
 xor   $t2 , $t7 , $t6 
 addiu   $t0 , $t1 , 2454295570 
 mult  $t5 , $t6 
 add $0, $0, $0
 mflo  $t2 
 xor   $t3 , $t6 , $t1 
 sw   $t4 , 0($a0) 
 addu   $t4 , $t6 , $t1 
 xori   $t6 , $t1 , 1099594545 
 lh   $t0 , 0($a0) 
 mult  $t7 , $t7 
 add $0, $0, $0
 mflo  $t5 
 ori   $t5 , $t5 , 2624394595 
 or   $t2 , $t5 , $t2 
 andi   $t5 , $t7 , 3853659050 
 sb   $t4 , 0($a0) 
 mult  $t6 , $t5 
 add $0, $0, $0
 mflo  $t0 
 lhu   $t1 , 0($a0) 
 or   $t3 , $t3 , $t6 
 mult  $t3 , $t7 
 add $0, $0, $0
 mflo  $t4 
 nor   $t1 , $t5 , $t2 
 multu  $t4 , $t3 
 add $0, $0, $0
 mflo  $t7 
 multu  $t7 , $t4 
 add $0, $0, $0
 mflo  $t0 
 nor   $t1 , $t0 , $t2 
 multu  $t6 , $t1 
 add $0, $0, $0
 mflo  $t0 
 xor   $t4 , $t5 , $t6 
 addiu   $t2 , $t7 , 2201259030 
 lb   $t5 , 0($a0) 
 mult  $t6 , $t7 
 mult  $t3 , $t3 
 add $0, $0, $0
 mflo  $t7 
 addiu   $t1 , $t1 , 1068427805 
 mult  $t1 , $t6 
 add $0, $0, $0
 mflo  $t6 
 nor   $t4 , $t4 , $t3 
 lb   $t5 , 0($a0) 
 and   $t6 , $t4 , $t5 
 mult  $t6 , $t2 
 add $0, $0, $0
 mflo  $t4 
 mult  $t2 , $t6 
 mult  $t0 , $t3 
 add $0, $0, $0
 mflo  $t4 
 subu   $t5 , $t4 , $t0 
 lhu   $t4 , 0($a0) 
 lw   $t6 , 0($a0) 
 nor   $t3 , $t1 , $t1 
 addu   $t0 , $t6 , $t4 
 mult  $t1 , $t3 
 mult  $t2 , $t2 
 add $0, $0, $0
 mflo  $t4 
 mult  $t7 , $t2 
 add $0, $0, $0
 mflo  $t0 
 mult  $t5 , $t4 
 mult  $t4 , $t0 
 add $0, $0, $0
 mflo  $t1 
 addu   $t0 , $t3 , $t5 
 lbu   $t4 , 0($a0) 
 multu  $t1 , $t2 
 add $0, $0, $0
 mflo  $t5 
 xori   $t3 , $t7 , 3290473997 
 xor   $t5 , $t6 , $t2 
 sb   $t6 , 0($a0) 
 addu   $t3 , $t4 , $t4 
 xor   $t6 , $t5 , $t7 
 ori   $t2 , $t6 , 949577296 
 multu  $t2 , $t3 
 add $0, $0, $0
 mflo  $t5 
 subu   $t2 , $t4 , $t3 
 mult  $t0 , $t3 
 mult  $t5 , $t5 
 add $0, $0, $0
 mflo  $t7 
 mult  $t2 , $t5 
 mult  $t1 , $t6 
 add $0, $0, $0
 mflo  $t5 
 mult  $t4 , $t7 
 mult  $t1 , $t5 
 add $0, $0, $0
 mflo  $t4 
 addiu   $t4 , $t0 , 3253665318 
 sb   $t1 , 0($a0) 
 sh   $t4 , 0($a0) 
 xori   $t5 , $t4 , 4245638797 
 andi   $t6 , $t1 , 2275626112 
 xori   $t3 , $t1 , 1680243516 
 andi   $t6 , $t0 , 197045518 
 andi   $t1 , $t1 , 2324474067 
 multu  $t6 , $t1 
 add $0, $0, $0
 mflo  $t4 
 lhu   $t5 , 0($a0) 
 sw   $t3 , 0($a0) 
 mult  $t0 , $t4 
 add $0, $0, $0
 mflo  $t1 
 mult  $t6 , $t4 
 add $0, $0, $0
 mflo  $t5 
 sw   $t0 , 0($a0) 
 xor   $t2 , $t1 , $t0 
 andi   $t1 , $t5 , 3818857959 
 andi   $t4 , $t1 , 1902369558 
 ori   $t3 , $t3 , 3646700015 
 mult  $t4 , $t5 
 add $0, $0, $0
 mflo  $t4 
 nor   $t1 , $t5 , $t6 
 addiu   $t6 , $t3 , 847475207 
 sw   $t5 , 0($a0) 
 mult  $t4 , $t3 
 add $0, $0, $0
 mflo  $t7 
 andi   $t1 , $t2 , 197036014 
 addiu   $t7 , $t0 , 2111558153 
 multu  $t0 , $t4 
 add $0, $0, $0
 mflo  $t1 
 or   $t0 , $t7 , $t1 
 lbu   $t1 , 0($a0) 
 andi   $t5 , $t0 , 3377408069 
 andi   $t5 , $t7 , 813326967 
 xori   $t1 , $t6 , 2312920628 
 multu  $t5 , $t6 
 add $0, $0, $0
 mflo  $t1 
 xori   $t7 , $t7 , 1230350243 
 lhu   $t7 , 0($a0) 
 or   $t4 , $t2 , $t0 
 ori   $t1 , $t1 , 1922100904 
 xori   $t4 , $t1 , 2916276813 
 sw   $t1 , 0($a0) 
 sh   $t3 , 0($a0) 
 and   $t4 , $t7 , $t6 
 sb   $t7 , 0($a0) 
 lbu   $t1 , 0($a0) 
 lhu   $t1 , 0($a0) 
 multu  $t4 , $t2 
 add $0, $0, $0
 mflo  $t4 
 sw   $t7 , 0($a0) 
 subu   $t2 , $t6 , $t3 
 or   $t0 , $t4 , $t7 
 or   $t2 , $t6 , $t2 
 lw   $t0 , 0($a0) 
 multu  $t3 , $t1 
 add $0, $0, $0
 mflo  $t5 
 sw   $t6 , 0($a0) 
 ori   $t1 , $t1 , 2561148731 
 or   $t6 , $t3 , $t7 
 ori   $t3 , $t0 , 1561603377 
 lhu   $t0 , 0($a0) 
 addu   $t0 , $t3 , $t4 
 subu   $t5 , $t1 , $t4 
 mult  $t4 , $t6 
 mult  $t6 , $t3 
 add $0, $0, $0
 mflo  $t6 
 addiu   $t2 , $t7 , 3500626510 
 addiu   $t1 , $t5 , 2536984013 
 mult  $t2 , $t1 
 mult  $t7 , $t1 
 add $0, $0, $0
 mflo  $t3 
 mult  $t0 , $t3 
 add $0, $0, $0
 mflo  $t4 
 multu  $t5 , $t5 
 add $0, $0, $0
 mflo  $t5 
 nor   $t5 , $t0 , $t7 
 ori   $t5 , $t2 , 740504333 
 subu   $t4 , $t6 , $t5 
 or   $t3 , $t7 , $t0 
 xori   $t1 , $t7 , 2124745784 
 andi   $t4 , $t5 , 3965461772 
 multu  $t3 , $t3 
 add $0, $0, $0
 mflo  $t5 
 lw   $t4 , 0($a0) 
 lhu   $t1 , 0($a0) 
 mult  $t2 , $t5 
 mult  $t5 , $t5 
 add $0, $0, $0
 mflo  $t0 
 multu  $t4 , $t0 
 add $0, $0, $0
 mflo  $t6 
 lh   $t7 , 0($a0) 
 andi   $t1 , $t7 , 1974635688 
 lbu   $t5 , 0($a0) 
 lh   $t0 , 0($a0) 
 ori   $t4 , $t7 , 2566416583 
 andi   $t0 , $t6 , 429477744 
 lb   $t5 , 0($a0) 
 andi   $t4 , $t5 , 3834899596 
 xori   $t2 , $t4 , 116152838 
 or   $t5 , $t5 , $t5 
 andi   $t5 , $t2 , 1286891887 
 nor   $t4 , $t6 , $t7 
 sh   $t3 , 0($a0) 
 sh   $t1 , 0($a0) 
 andi   $t7 , $t5 , 589811144 
 mult  $t0 , $t0 
 add $0, $0, $0
 mflo  $t6 
 addiu   $t1 , $t2 , 1687269506 
 mult  $t3 , $t0 
 mult  $t7 , $t7 
 add $0, $0, $0
 mflo  $t6 
 ori   $t0 , $t0 , 1341240256 
 mult  $t0 , $t6 
 add $0, $0, $0
 mflo  $t1 
 xori   $t6 , $t6 , 590420922 
 and   $t2 , $t1 , $t6 
 subu   $t6 , $t6 , $t1 
 xor   $t5 , $t3 , $t7 
 addiu   $t4 , $t7 , 2821933152 
 multu  $t7 , $t7 
 add $0, $0, $0
 mflo  $t1 
 addiu   $t2 , $t7 , 669583076 
 lb   $t5 , 0($a0) 
 lbu   $t7 , 0($a0) 
 mult  $t0 , $t0 
 add $0, $0, $0
 mflo  $t2 
 xor   $t6 , $t5 , $t5 
 andi   $t4 , $t4 , 336853711 
 mult  $t1 , $t0 
 add $0, $0, $0
 mflo  $t7 
 ori   $t0 , $t6 , 2083350294 
 xori   $t5 , $t1 , 2329535654 
 andi   $t4 , $t3 , 657933008 
 multu  $t0 , $t4 
 add $0, $0, $0
 mflo  $t0 
 addu   $t1 , $t6 , $t4 
 multu  $t4 , $t5 
 add $0, $0, $0
 mflo  $t4 
 lbu   $t1 , 0($a0) 
 and   $t6 , $t7 , $t6 
 nor   $t6 , $t3 , $t6 
 addu   $t1 , $t1 , $t7 
 xor   $t0 , $t2 , $t5 
 multu  $t4 , $t0 
 add $0, $0, $0
 mflo  $t3 
 subu   $t5 , $t6 , $t7 
 andi   $t6 , $t6 , 1008739997 
 multu  $t0 , $t0 
 add $0, $0, $0
 mflo  $t5 
 addiu   $t3 , $t4 , 4273183914 
 sh   $t3 , 0($a0) 
 mult  $t2 , $t4 
 add $0, $0, $0
 mflo  $t5 
 xori   $t7 , $t1 , 4270361710 
 mult  $t6 , $t1 
 mult  $t1 , $t4 
 add $0, $0, $0
 mflo  $t0 
 nor   $t3 , $t5 , $t3 
 nor   $t0 , $t3 , $t7 
 sb   $t2 , 0($a0) 
 mult  $t4 , $t3 
 mult  $t4 , $t4 
 add $0, $0, $0
 mflo  $t6 
 sw   $t1 , 0($a0) 
 nor   $t0 , $t2 , $t7 
 xor   $t2 , $t3 , $t6 
 addu   $t6 , $t2 , $t1 
 sh   $t4 , 0($a0) 
 mult  $t2 , $t6 
 mult  $t3 , $t2 
 add $0, $0, $0
 mflo  $t6 
 and   $t4 , $t5 , $t0 
 mult  $t7 , $t2 
 mult  $t0 , $t1 
 add $0, $0, $0
 mflo  $t3 
 nor   $t7 , $t5 , $t1 
 sb   $t7 , 0($a0) 
 multu  $t4 , $t3 
 add $0, $0, $0
 mflo  $t4 
 mult  $t6 , $t3 
 add $0, $0, $0
 mflo  $t2 
 lh   $t5 , 0($a0) 
 nor   $t0 , $t4 , $t7 
 addiu   $t5 , $t4 , 2891979293 
 mult  $t0 , $t5 
 mult  $t3 , $t5 
 add $0, $0, $0
 mflo  $t1 
 ori   $t1 , $t6 , 2690434126 
 multu  $t5 , $t7 
 add $0, $0, $0
 mflo  $t3 
 andi   $t7 , $t5 , 2446968440 
 andi   $t3 , $t3 , 877972051 
 ori   $t4 , $t3 , 2826356203 
 mult  $t5 , $t5 
 add $0, $0, $0
 mflo  $t3 
 and   $t3 , $t3 , $t5 
 lhu   $t3 , 0($a0) 
 addiu   $t0 , $t0 , 3774898280 
 addiu   $t2 , $t3 , 2417821408 
 xor   $t7 , $t5 , $t0 
 xor   $t2 , $t2 , $t4 
 nor   $t5 , $t4 , $t2 
 and   $t7 , $t3 , $t0 
 or   $t1 , $t6 , $t3 
 sw   $t1 , 0($a0) 
 sh   $t3 , 0($a0) 
 multu  $t5 , $t4 
 add $0, $0, $0
 mflo  $t3 
 addu   $t1 , $t3 , $t7 
 sh   $t3 , 0($a0) 
 addu   $t6 , $t7 , $t2 
 sw   $t6 , 0($a0) 
 mult  $t7 , $t2 
 mult  $t3 , $t7 
 add $0, $0, $0
 mflo  $t6 
 addu   $t4 , $t2 , $t4 
 lh   $t5 , 0($a0) 
 lh   $t5 , 0($a0) 
 andi   $t7 , $t7 , 830583110 
 or   $t6 , $t1 , $t1 
 mult  $t2 , $t6 
 mult  $t0 , $t6 
 add $0, $0, $0
 mflo  $t5 
 subu   $t2 , $t7 , $t0 
 nor   $t5 , $t2 , $t1 
 lb   $t3 , 0($a0) 
 andi   $t2 , $t6 , 2501028881 
 or   $t6 , $t0 , $t5 
 andi   $t0 , $t0 , 3215697004 
 sh   $t1 , 0($a0) 
 multu  $t4 , $t0 
 add $0, $0, $0
 mflo  $t0 
 and   $t6 , $t2 , $t1 
 multu  $t1 , $t5 
 add $0, $0, $0
 mflo  $t2 
 addiu   $t6 , $t2 , 1913669785 
 mult  $t7 , $t6 
 mult  $t3 , $t6 
 add $0, $0, $0
 mflo  $t4 
 multu  $t2 , $t0 
 add $0, $0, $0
 mflo  $t4 
 addu   $t2 , $t3 , $t4 
 lb   $t5 , 0($a0) 
 lw   $t4 , 0($a0) 
 sb   $t2 , 0($a0) 
 mult  $t5 , $t7 
 mult  $t6 , $t7 
 add $0, $0, $0
 mflo  $t0 
 andi   $t3 , $t6 , 2620501977 
 subu   $t4 , $t2 , $t3 
 addu   $t0 , $t0 , $t1 
 sw   $t6 , 0($a0) 
 multu  $t5 , $t3 
 add $0, $0, $0
 mflo  $t5 
 multu  $t0 , $t1 
 add $0, $0, $0
 mflo  $t3 
 mult  $t4 , $t6 
 mult  $t0 , $t2 
 add $0, $0, $0
 mflo  $t6 
 multu  $t6 , $t5 
 add $0, $0, $0
 mflo  $t4 
 and   $t1 , $t5 , $t7 
 mult  $t1 , $t6 
 add $0, $0, $0
 mflo  $t7 
 sb   $t4 , 0($a0) 
 xor   $t6 , $t1 , $t0 
 addu   $t0 , $t2 , $t2 
 mult  $t3 , $t3 
 mult  $t4 , $t0 
 add $0, $0, $0
 mflo  $t6 
 lb   $t3 , 0($a0) 
 xori   $t7 , $t4 , 2282483866 
 subu   $t4 , $t5 , $t5 
 addiu   $t2 , $t3 , 3709352878 
 mult  $t6 , $t1 
 mult  $t1 , $t4 
 add $0, $0, $0
 mflo  $t1 
 xor   $t6 , $t6 , $t1 
 mult  $t1 , $t2 
 mult  $t3 , $t1 
 add $0, $0, $0
 mflo  $t0 
 lw   $t5 , 0($a0) 
 multu  $t6 , $t7 
 add $0, $0, $0
 mflo  $t1 
 mult  $t6 , $t1 
 mult  $t1 , $t4 
 add $0, $0, $0
 mflo  $t1 
 nor   $t7 , $t1 , $t2 
 xor   $t7 , $t1 , $t4 
 multu  $t3 , $t6 
 add $0, $0, $0
 mflo  $t0 
 mult  $t4 , $t1 
 add $0, $0, $0
 mflo  $t1 
 multu  $t0 , $t4 
 add $0, $0, $0
 mflo  $t3 
 mult  $t5 , $t0 
 add $0, $0, $0
 mflo  $t0 
 xori   $t1 , $t4 , 1367028567 
 and   $t0 , $t4 , $t0 
 mult  $t1 , $t0 
 add $0, $0, $0
 mflo  $t2 
 ori   $t1 , $t2 , 2273779739 
 multu  $t7 , $t4 
 add $0, $0, $0
 mflo  $t3 
 or   $t4 , $t7 , $t2 
 nor   $t0 , $t4 , $t7 
 sw   $t1 , 0($a0) 
 or   $t4 , $t5 , $t2 
 sw   $t3 , 0($a0) 
 ori   $t5 , $t3 , 2182954576 
 lw   $t2 , 0($a0) 
 addu   $t6 , $t0 , $t7 
 andi   $t7 , $t7 , 3225792870 
 mult  $t4 , $t3 
 add $0, $0, $0
 mflo  $t2 
 addu   $t0 , $t5 , $t3 
 multu  $t0 , $t6 
 add $0, $0, $0
 mflo  $t3 
 nor   $t0 , $t7 , $t2 
 sb   $t1 , 0($a0) 
 andi   $t7 , $t4 , 4015977566 
 multu  $t2 , $t0 
 add $0, $0, $0
 mflo  $t2 
 sh   $t4 , 0($a0) 
 or   $t5 , $t4 , $t2 
 multu  $t1 , $t0 
 add $0, $0, $0
 mflo  $t2 
 sh   $t1 , 0($a0) 
 addu   $t3 , $t1 , $t0 
 and   $t0 , $t5 , $t3 
 addu   $t1 , $t1 , $t0 
 ori   $t4 , $t5 , 1254346236 
 andi   $t0 , $t2 , 3365701245 
 ori   $t0 , $t0 , 474188079 
 xori   $t1 , $t5 , 1248696358 
 addu   $t6 , $t1 , $t7 
 nor   $t1 , $t5 , $t1 
 addiu   $t1 , $t6 , 17797112 
 multu  $t0 , $t5 
 add $0, $0, $0
 mflo  $t5 
 mult  $t4 , $t2 
 mult  $t5 , $t7 
 add $0, $0, $0
 mflo  $t6 
 ori   $t4 , $t4 , 1953102246 
 subu   $t4 , $t6 , $t3 
 subu   $t4 , $t0 , $t1 
 addiu   $t3 , $t2 , 3755475701 
 mult  $t6 , $t1 
 add $0, $0, $0
 mflo  $t1 
 sh   $t2 , 0($a0) 
 addiu   $t5 , $t1 , 2780068017 
 sh   $t3 , 0($a0) 
 nor   $t5 , $t2 , $t5 
 xori   $t3 , $t3 , 2382568275 
 multu  $t3 , $t1 
 add $0, $0, $0
 mflo  $t6 
 sb   $t2 , 0($a0) 
 lb   $t3 , 0($a0) 
 addiu   $t7 , $t4 , 2520637873 
 andi   $t0 , $t7 , 496727221 
 xor   $t2 , $t1 , $t0 
 lbu   $t7 , 0($a0) 
 and   $t5 , $t2 , $t6 
 xori   $t2 , $t2 , 247667139 
 lh   $t0 , 0($a0) 
 mult  $t3 , $t1 
 mult  $t0 , $t1 
 add $0, $0, $0
 mflo  $t0 
 lw   $t1 , 0($a0) 
 sb   $t2 , 0($a0) 
 mult  $t1 , $t6 
 mult  $t5 , $t4 
 add $0, $0, $0
 mflo  $t4 
 lb   $t7 , 0($a0) 
 and   $t3 , $t2 , $t4 
 multu  $t6 , $t7 
 add $0, $0, $0
 mflo  $t5 
 or   $t0 , $t0 , $t5 
 ori   $t0 , $t0 , 1661682345 
 xor   $t2 , $t1 , $t6 
 multu  $t2 , $t6 
 add $0, $0, $0
 mflo  $t2 
 mult  $t1 , $t7 
 mult  $t5 , $t5 
 add $0, $0, $0
 mflo  $t0 
 and   $t2 , $t0 , $t2 
 sw   $t1 , 0($a0) 
 lb   $t0 , 0($a0) 
 lbu   $t3 , 0($a0) 
 mult  $t3 , $t5 
 mult  $t3 , $t7 
 add $0, $0, $0
 mflo  $t2 
 mult  $t7 , $t6 
 mult  $t6 , $t6 
 add $0, $0, $0
 mflo  $t1 
 xori   $t3 , $t1 , 657741324 
 andi   $t1 , $t4 , 1633634374 
 xor   $t3 , $t2 , $t1 
 addiu   $t1 , $t5 , 1302327332 
 andi   $t1 , $t2 , 1894480478 
 xori   $t5 , $t1 , 1044525528 
 ori   $t1 , $t7 , 1199695484 
 xori   $t3 , $t0 , 123117146 
 lbu   $t6 , 0($a0) 
 nor   $t2 , $t5 , $t5 
 nor   $t0 , $t0 , $t4 
 andi   $t2 , $t4 , 1857122635 
 nor   $t2 , $t6 , $t4 
 ori   $t6 , $t1 , 1548079938 
 lbu   $t7 , 0($a0) 
 multu  $t4 , $t3 
 add $0, $0, $0
 mflo  $t1 
 nor   $t6 , $t2 , $t2 
 multu  $t7 , $t0 
 add $0, $0, $0
 mflo  $t7 
 mult  $t0 , $t3 
 mult  $t6 , $t7 
 add $0, $0, $0
 mflo  $t4 
 xori   $t5 , $t4 , 2764569029 
 subu   $t5 , $t6 , $t7 
 or   $t4 , $t2 , $t3 
 nor   $t5 , $t1 , $t3 
 xori   $t3 , $t0 , 917380215 
 andi   $t4 , $t0 , 2685204644 
 lh   $t1 , 0($a0) 
 lb   $t3 , 0($a0) 
 multu  $t5 , $t3 
 add $0, $0, $0
 mflo  $t4 
 sw   $t6 , 0($a0) 
 ori   $t5 , $t4 , 1852756363 
 mult  $t7 , $t7 
 mult  $t1 , $t1 
 add $0, $0, $0
 mflo  $t7 
 mult  $t6 , $t4 
 mult  $t3 , $t1 
 add $0, $0, $0
 mflo  $t5 
 mult  $t5 , $t6 
 add $0, $0, $0
 mflo  $t5 
 mult  $t3 , $t1 
 add $0, $0, $0
 mflo  $t5 
 addiu   $t1 , $t3 , 1131140786 
 or   $t6 , $t5 , $t0 
 ori   $t0 , $t1 , 3507989126 
 subu   $t3 , $t1 , $t0 
 sh   $t4 , 0($a0) 
 mult  $t1 , $t3 
 add $0, $0, $0
 mflo  $t6 
 addiu   $t1 , $t3 , 919080376 
 lbu   $t2 , 0($a0) 
 mult  $t7 , $t1 
 mult  $t3 , $t6 
 add $0, $0, $0
 mflo  $t7 
 lb   $t7 , 0($a0) 
 sb   $t2 , 0($a0) 
 addu   $t3 , $t0 , $t4 
 addiu   $t0 , $t2 , 2582700606 
 lw   $t0 , 0($a0) 
 mult  $t2 , $t2 
 add $0, $0, $0
 mflo  $t3 
 xori   $t2 , $t2 , 2514552265 
 ori   $t7 , $t2 , 29147640 
 subu   $t3 , $t1 , $t0 
 mult  $t4 , $t7 
 add $0, $0, $0
 mflo  $t2 
 sh   $t5 , 0($a0) 
 and   $t2 , $t6 , $t1 
 or   $t5 , $t5 , $t7 
 mult  $t6 , $t0 
 add $0, $0, $0
 mflo  $t7 
 lh   $t3 , 0($a0) 
 addiu   $t0 , $t5 , 4096457371 
 andi   $t6 , $t0 , 4236229283 
 nor   $t2 , $t7 , $t3 
 lbu   $t4 , 0($a0) 
 ori   $t2 , $t0 , 3082026095 
 ori   $t5 , $t3 , 4188856340 
 mult  $t0 , $t1 
 add $0, $0, $0
 mflo  $t1 
 multu  $t0 , $t6 
 add $0, $0, $0
 mflo  $t3 
 sh   $t6 , 0($a0) 
 lh   $t1 , 0($a0) 
 nor   $t0 , $t0 , $t1 
 mult  $t0 , $t1 
 mult  $t3 , $t0 
 add $0, $0, $0
 mflo  $t5 
 addu   $t6 , $t0 , $t4 
 mult  $t4 , $t4 
 add $0, $0, $0
 mflo  $t3 
 sh   $t1 , 0($a0) 
 subu   $t6 , $t4 , $t0 
 mult  $t5 , $t7 
 add $0, $0, $0
 mflo  $t5 
 ori   $t7 , $t1 , 223005909 
 multu  $t2 , $t6 
 add $0, $0, $0
 mflo  $t7 
 addiu   $t2 , $t6 , 3028921899 
 mult  $t0 , $t5 
 mult  $t6 , $t5 
 add $0, $0, $0
 mflo  $t3 
 or   $t5 , $t0 , $t2 
 sw   $t6 , 0($a0) 
 sb   $t5 , 0($a0) 
 addu   $t3 , $t7 , $t5 
 sh   $t5 , 0($a0) 
 lh   $t7 , 0($a0) 
 mult  $t7 , $t0 
 add $0, $0, $0
 mflo  $t3 
 sw   $t4 , 0($a0) 
 mult  $t7 , $t5 
 add $0, $0, $0
 mflo  $t7 
 addu   $t3 , $t1 , $t7 
 lh   $t3 , 0($a0) 
 sw   $t2 , 0($a0) 
 multu  $t7 , $t4 
 add $0, $0, $0
 mflo  $t2 
 andi   $t1 , $t3 , 2561532176 
 mult  $t4 , $t2 
 mult  $t0 , $t3 
 add $0, $0, $0
 mflo  $t5 
 mult  $t1 , $t7 
 add $0, $0, $0
 mflo  $t6 
 nor   $t3 , $t4 , $t0 
 lh   $t7 , 0($a0) 
 or   $t0 , $t0 , $t4 
 lhu   $t2 , 0($a0) 
 lw   $t4 , 0($a0) 
 lbu   $t1 , 0($a0) 
 multu  $t7 , $t0 
 add $0, $0, $0
 mflo  $t3 
 sw   $t3 , 0($a0) 
 lh   $t3 , 0($a0) 
 mult  $t2 , $t7 
 mult  $t7 , $t2 
 add $0, $0, $0
 mflo  $t7 
 or   $t1 , $t1 , $t1 
 xori   $t3 , $t3 , 2452159416 
 lb   $t0 , 0($a0) 
 addiu   $t4 , $t2 , 660726417 
 ori   $t0 , $t7 , 3377744275 
 ori   $t6 , $t4 , 1396379042 
 addiu   $t1 , $t3 , 2442614754 
 ori   $t7 , $t0 , 2437355185 
 or   $t0 , $t7 , $t5 
 lb   $t0 , 0($a0) 
 mult  $t5 , $t7 
 add $0, $0, $0
 mflo  $t2 
 ori   $t4 , $t6 , 3016117631 
 sb   $t2 , 0($a0) 
 addiu   $t7 , $t2 , 1889033332 
 lhu   $t5 , 0($a0) 
 and   $t2 , $t4 , $t6 
 sw   $t3 , 0($a0) 
 nor   $t5 , $t5 , $t1 
 xori   $t1 , $t4 , 1555871643 
 addu   $t1 , $t5 , $t6 
 mult  $t0 , $t2 
 mult  $t4 , $t3 
 add $0, $0, $0
 mflo  $t3 
 or   $t4 , $t2 , $t0 
 and   $t7 , $t3 , $t0 
 nor   $t6 , $t7 , $t1 
 mult  $t7 , $t2 
 mult  $t1 , $t2 
 add $0, $0, $0
 mflo  $t7 
 multu  $t4 , $t3 
 add $0, $0, $0
 mflo  $t5 
 mult  $t6 , $t6 
 mult  $t5 , $t7 
 add $0, $0, $0
 mflo  $t3 
 addiu   $t4 , $t2 , 889675687 
 mult  $t6 , $t7 
 add $0, $0, $0
 mflo  $t5 
 xor   $t0 , $t2 , $t2 
 sh   $t4 , 0($a0) 
 mult  $t0 , $t4 
 mult  $t7 , $t1 
 add $0, $0, $0
 mflo  $t4 
 mult  $t1 , $t3 
 mult  $t6 , $t1 
 add $0, $0, $0
 mflo  $t4 
 mult  $t7 , $t4 
 add $0, $0, $0
 mflo  $t4 
 mult  $t2 , $t4 
 mult  $t2 , $t5 
 add $0, $0, $0
 mflo  $t2 
 mult  $t7 , $t6 
 mult  $t5 , $t6 
 add $0, $0, $0
 mflo  $t1 
 sh   $t3 , 0($a0) 
 multu  $t4 , $t0 
 add $0, $0, $0
 mflo  $t6 
 lw   $t5 , 0($a0) 
 nor   $t2 , $t6 , $t5 
 multu  $t4 , $t1 
 add $0, $0, $0
 mflo  $t1 
 lh   $t1 , 0($a0) 
 sw   $t1 , 0($a0) 
 mult  $t5 , $t4 
 mult  $t2 , $t4 
 add $0, $0, $0
 mflo  $t5 
 nor   $t4 , $t3 , $t5 
 andi   $t2 , $t7 , 2990758217 
 ori   $t6 , $t7 , 3859214671 
 lh   $t1 , 0($a0) 
 lh   $t4 , 0($a0) 
 multu  $t6 , $t5 
 add $0, $0, $0
 mflo  $t7 
 andi   $t7 , $t4 , 581232044 
 multu  $t1 , $t3 
 add $0, $0, $0
 mflo  $t5 
 xori   $t5 , $t0 , 3178170739 
 ori   $t3 , $t0 , 2598904312 
 mult  $t1 , $t5 
 mult  $t6 , $t3 
 add $0, $0, $0
 mflo  $t6 
 mult  $t4 , $t1 
 mult  $t4 , $t7 
 add $0, $0, $0
 mflo  $t4 
 lhu   $t1 , 0($a0) 
 nor   $t7 , $t4 , $t6 
 multu  $t6 , $t7 
 add $0, $0, $0
 mflo  $t3 
 mult  $t4 , $t4 
 add $0, $0, $0
 mflo  $t2 
 multu  $t2 , $t5 
 add $0, $0, $0
 mflo  $t7 
 and   $t0 , $t7 , $t0 
 sh   $t2 , 0($a0) 
 subu   $t2 , $t2 , $t2 
 mult  $t6 , $t5 
 mult  $t5 , $t7 
 add $0, $0, $0
 mflo  $t0 
 multu  $t4 , $t0 
 add $0, $0, $0
 mflo  $t7 
 addiu   $t3 , $t2 , 3907943079 
 andi   $t2 , $t1 , 2164316291 
 addu   $t7 , $t1 , $t4 
 or   $t6 , $t7 , $t1 
 and   $t6 , $t5 , $t0 
 lw   $t6 , 0($a0) 
 sh   $t5 , 0($a0) 
 addu   $t4 , $t1 , $t3 
 mult  $t2 , $t1 
 mult  $t7 , $t0 
 add $0, $0, $0
 mflo  $t6 
 addiu   $t4 , $t1 , 521023170 
 nor   $t1 , $t6 , $t7 
 lb   $t5 , 0($a0) 
 addiu   $t4 , $t7 , 968463570 
 subu   $t7 , $t1 , $t4 
 sw   $t2 , 0($a0) 
 multu  $t3 , $t3 
 add $0, $0, $0
 mflo  $t3 
 or   $t3 , $t5 , $t7 
 mult  $t7 , $t7 
 mult  $t4 , $t7 
 add $0, $0, $0
 mflo  $t6 
 and   $t2 , $t0 , $t4 
 xor   $t7 , $t7 , $t4 
 sb   $t2 , 0($a0) 
 lhu   $t5 , 0($a0) 
 lbu   $t7 , 0($a0) 
 multu  $t0 , $t4 
 add $0, $0, $0
 mflo  $t4 
 addiu   $t0 , $t6 , 3494039055 
 mult  $t5 , $t5 
 add $0, $0, $0
 mflo  $t0 
 mult  $t6 , $t1 
 mult  $t7 , $t3 
 add $0, $0, $0
 mflo  $t3 
 and   $t4 , $t0 , $t6 
 xori   $t3 , $t6 , 2628221723 
 and   $t0 , $t7 , $t7 
 xor   $t7 , $t0 , $t1 
 addu   $t7 , $t7 , $t4 
 ori   $t7 , $t7 , 2381175121 
 addiu   $t2 , $t2 , 4029479858 
 or   $t3 , $t5 , $t0 
 xor   $t5 , $t2 , $t5 
 addu   $t0 , $t6 , $t4 
 lb   $t5 , 0($a0) 
 addiu   $t3 , $t2 , 4160395184 
 lh   $t6 , 0($a0) 
 mult  $t3 , $t4 
 add $0, $0, $0
 mflo  $t6 
 subu   $t1 , $t5 , $t2 
 lh   $t2 , 0($a0) 
 lbu   $t4 , 0($a0) 
 multu  $t6 , $t3 
 add $0, $0, $0
 mflo  $t6 
 xori   $t7 , $t7 , 1505673939 
 xor   $t1 , $t0 , $t2 
 sw   $t3 , 0($a0) 
 subu   $t0 , $t0 , $t5 
 mult  $t3 , $t1 
 add $0, $0, $0
 mflo  $t1 
 sb   $t7 , 0($a0) 
 lb   $t0 , 0($a0) 
 xor   $t1 , $t5 , $t2 
 andi   $t1 , $t2 , 4010877323 
 subu   $t4 , $t4 , $t2 
 andi   $t1 , $t1 , 1320283561 
 ori   $t3 , $t0 , 3136075267 
 multu  $t0 , $t7 
 add $0, $0, $0
 mflo  $t6 
 xor   $t7 , $t5 , $t3 
 addiu   $t1 , $t2 , 505432809 
 xori   $t5 , $t1 , 3664350337 
 mult  $t4 , $t3 
 mult  $t6 , $t1 
 add $0, $0, $0
 mflo  $t1 
 lw   $t1 , 0($a0) 
 nor   $t7 , $t3 , $t5 
 mult  $t5 , $t5 
 mult  $t2 , $t5 
 add $0, $0, $0
 mflo  $t1 
 addiu   $t5 , $t5 , 2045932256 
 mult  $t2 , $t1 
 add $0, $0, $0
 mflo  $t7 
 mult  $t4 , $t5 
 mult  $t1 , $t2 
 add $0, $0, $0
 mflo  $t4 
 ori   $t3 , $t1 , 2010574382 
 lb   $t6 , 0($a0) 
 multu  $t7 , $t2 
 add $0, $0, $0
 mflo  $t6 
 addiu   $t3 , $t6 , 245244961 
 mult  $t0 , $t7 
 mult  $t5 , $t0 
 add $0, $0, $0
 mflo  $t5 
 ori   $t5 , $t1 , 240385544 
 mult  $t0 , $t3 
 mult  $t1 , $t0 
 add $0, $0, $0
 mflo  $t6 
 and   $t1 , $t6 , $t3 
 mult  $t0 , $t5 
 add $0, $0, $0
 mflo  $t6 
 lh   $t4 , 0($a0) 
 multu  $t0 , $t3 
 add $0, $0, $0
 mflo  $t7 
 xori   $t7 , $t3 , 1122352737 
 addiu   $t4 , $t7 , 1264267191 
 ori   $t2 , $t6 , 30823201 
 addu   $t2 , $t6 , $t0 
 lw   $t4 , 0($a0) 
 addiu   $t2 , $t5 , 3991584168 
 xori   $t7 , $t6 , 683588251 
 xor   $t4 , $t5 , $t6 
 lbu   $t1 , 0($a0) 
 multu  $t4 , $t2 
 add $0, $0, $0
 mflo  $t4 
 andi   $t2 , $t5 , 2323375270 
 sb   $t4 , 0($a0) 
 mult  $t5 , $t2 
 add $0, $0, $0
 mflo  $t0 
 mult  $t4 , $t4 
 mult  $t4 , $t4 
 add $0, $0, $0
 mflo  $t2 
 lbu   $t0 , 0($a0) 
 sb   $t0 , 0($a0) 
 andi   $t4 , $t4 , 203392363 
 multu  $t4 , $t3 
 add $0, $0, $0
 mflo  $t3 
 sw   $t1 , 0($a0) 
 addu   $t1 , $t7 , $t0 
 lw   $t2 , 0($a0) 
 andi   $t0 , $t0 , 2565377679 
 multu  $t0 , $t2 
 add $0, $0, $0
 mflo  $t2 
 sh   $t5 , 0($a0) 
 lb   $t7 , 0($a0) 
 and   $t6 , $t7 , $t0 
 andi   $t2 , $t6 , 3599463798 
 lbu   $t2 , 0($a0) 
 sb   $t1 , 0($a0) 
 sb   $t4 , 0($a0) 
 lh   $t2 , 0($a0) 
 ori   $t0 , $t4 , 938734569 
 addiu   $t4 , $t6 , 2353742961 
 xor   $t3 , $t1 , $t6 
 or   $t2 , $t0 , $t0 
 lh   $t7 , 0($a0) 
 xor   $t7 , $t6 , $t6 
 multu  $t5 , $t3 
 add $0, $0, $0
 mflo  $t4 
 mult  $t7 , $t6 
 add $0, $0, $0
 mflo  $t5 
 and   $t7 , $t5 , $t3 
 lw   $t5 , 0($a0) 
 lw   $t6 , 0($a0) 
 lh   $t4 , 0($a0) 
 nor   $t3 , $t2 , $t4 
 xori   $t3 , $t4 , 1819142133 
 lw   $t7 , 0($a0) 
 nor   $t0 , $t3 , $t4 
 andi   $t3 , $t7 , 3276698681 
 sb   $t5 , 0($a0) 
 multu  $t0 , $t3 
 add $0, $0, $0
 mflo  $t1 
 xori   $t7 , $t2 , 216953186 
 ori   $t6 , $t1 , 2252983961 
 subu   $t2 , $t7 , $t4 
 mult  $t4 , $t1 
 mult  $t4 , $t4 
 add $0, $0, $0
 mflo  $t1 
 xori   $t4 , $t4 , 2482380745 
 or   $t0 , $t2 , $t1 
 nor   $t0 , $t1 , $t7 
 xor   $t3 , $t0 , $t2 
 sw   $t2 , 0($a0) 
 and   $t4 , $t4 , $t2 
 and   $t6 , $t6 , $t1 
 xori   $t3 , $t4 , 128588706 
 sw   $t0 , 0($a0) 
 nor   $t3 , $t5 , $t0 
 lw   $t2 , 0($a0) 
 ori   $t6 , $t5 , 3801636261 
 andi   $t5 , $t1 , 386873009 
 lh   $t4 , 0($a0) 
 mult  $t5 , $t0 
 add $0, $0, $0
 mflo  $t3 
 addiu   $t3 , $t4 , 3312811643 
 or   $t1 , $t3 , $t4 
 multu  $t2 , $t5 
 add $0, $0, $0
 mflo  $t4 
 lb   $t4 , 0($a0) 
 xori   $t4 , $t0 , 2581610790 
 lh   $t0 , 0($a0) 
 lhu   $t1 , 0($a0) 
 lbu   $t3 , 0($a0) 
 addiu   $t4 , $t0 , 1840277614 
 subu   $t0 , $t4 , $t3 
 sb   $t1 , 0($a0) 
 subu   $t1 , $t3 , $t2 
 lbu   $t7 , 0($a0) 
 ori   $t1 , $t0 , 3010861425 
 lhu   $t0 , 0($a0) 
 nor   $t1 , $t3 , $t5 
 multu  $t5 , $t6 
 add $0, $0, $0
 mflo  $t2 
 subu   $t1 , $t7 , $t7 
 multu  $t4 , $t3 
 add $0, $0, $0
 mflo  $t7 
 lhu   $t6 , 0($a0) 
 xori   $t3 , $t0 , 2658703227 
 lh   $t2 , 0($a0) 
 lhu   $t0 , 0($a0) 
 ori   $t0 , $t6 , 1256416759 
 xori   $t6 , $t3 , 159907395 
 xor   $t0 , $t2 , $t0 
 and   $t3 , $t2 , $t2 
 addiu   $t3 , $t0 , 2756279275 
 xori   $t5 , $t2 , 4120613020 
 nor   $t3 , $t2 , $t0 
 ori   $t0 , $t2 , 2687319045 
 mult  $t5 , $t3 
 mult  $t0 , $t0 
 add $0, $0, $0
 mflo  $t0 
 mult  $t5 , $t1 
 mult  $t6 , $t1 
 add $0, $0, $0
 mflo  $t3 
 addu   $t2 , $t2 , $t5 
 mult  $t5 , $t6 
 add $0, $0, $0
 mflo  $t6 
 mult  $t1 , $t3 
 add $0, $0, $0
 mflo  $t3 
 addiu   $t1 , $t1 , 812627473 
 ori   $t6 , $t0 , 504074122 
 ori   $t4 , $t5 , 1315894622 
 xor   $t3 , $t6 , $t7 
 mult  $t4 , $t0 
 mult  $t1 , $t1 
 add $0, $0, $0
 mflo  $t2 
 multu  $t6 , $t7 
 add $0, $0, $0
 mflo  $t4 
 lh   $t3 , 0($a0) 
 sw   $t5 , 0($a0) 
 multu  $t4 , $t4 
 add $0, $0, $0
 mflo  $t2 
 sh   $t1 , 0($a0) 
 mult  $t0 , $t0 
 mult  $t6 , $t3 
 add $0, $0, $0
 mflo  $t3 
 multu  $t4 , $t5 
 add $0, $0, $0
 mflo  $t4 
 lbu   $t2 , 0($a0) 
 nor   $t4 , $t4 , $t2 
 multu  $t3 , $t1 
 add $0, $0, $0
 mflo  $t5 
 multu  $t0 , $t0 
 add $0, $0, $0
 mflo  $t0 
 multu  $t3 , $t3 
 add $0, $0, $0
 mflo  $t7 
 addiu   $t5 , $t1 , 3453074212 
 sb   $t5 , 0($a0) 
 lbu   $t6 , 0($a0) 
 xori   $t5 , $t1 , 1879006353 
 mult  $t6 , $t4 
 mult  $t1 , $t7 
 add $0, $0, $0
 mflo  $t1 
 and   $t5 , $t0 , $t0 
 addu   $t0 , $t0 , $t7 
 multu  $t7 , $t6 
 add $0, $0, $0
 mflo  $t7 
 multu  $t0 , $t2 
 add $0, $0, $0
 mflo  $t7 
 nor   $t4 , $t1 , $t3 
 and   $t4 , $t7 , $t2 
 mult  $t1 , $t5 
 add $0, $0, $0
 mflo  $t1 
 or   $t3 , $t4 , $t2 
 addiu   $t3 , $t0 , 3819609277 
 and   $t2 , $t0 , $t2 
 addiu   $t3 , $t5 , 2361050052 
 ori   $t5 , $t1 , 3047772387 
 multu  $t0 , $t0 
 add $0, $0, $0
 mflo  $t4 
 ori   $t0 , $t7 , 3878384301 
 sh   $t1 , 0($a0) 
 lw   $t1 , 0($a0) 
 addiu   $t2 , $t0 , 4277177883 
 sw   $t4 , 0($a0) 
 sh   $t3 , 0($a0) 
 ori   $t7 , $t6 , 4027548693 
 lh   $t4 , 0($a0) 
 or   $t4 , $t6 , $t6 
 andi   $t6 , $t2 , 4149317270 
 nor   $t0 , $t7 , $t5 
 lbu   $t3 , 0($a0) 
 subu   $t5 , $t0 , $t5 
 or   $t1 , $t1 , $t0 
 xori   $t0 , $t0 , 792305269 
 addu   $t1 , $t6 , $t5 
 lw   $t2 , 0($a0) 
 multu  $t6 , $t5 
 add $0, $0, $0
 mflo  $t2 
 mult  $t6 , $t4 
 mult  $t4 , $t5 
 add $0, $0, $0
 mflo  $t3 
 sw   $t7 , 0($a0) 
 andi   $t5 , $t7 , 2212511716 
 lw   $t4 , 0($a0) 
 nor   $t4 , $t5 , $t6 
 or   $t4 , $t0 , $t7 
 mult  $t0 , $t7 
 mult  $t7 , $t7 
 add $0, $0, $0
 mflo  $t4 
 addiu   $t1 , $t2 , 3338475912 
 mult  $t1 , $t6 
 add $0, $0, $0
 mflo  $t3 
 andi   $t6 , $t0 , 817866407 
 or   $t7 , $t1 , $t1 
 nor   $t5 , $t7 , $t7 
 mult  $t5 , $t4 
 add $0, $0, $0
 mflo  $t3 
 addiu   $t5 , $t6 , 3001826415 
 mult  $t4 , $t5 
 add $0, $0, $0
 mflo  $t4 
 andi   $t4 , $t1 , 2418943962 
 lw   $t0 , 0($a0) 
 subu   $t5 , $t0 , $t4 
 or   $t5 , $t6 , $t7 
 subu   $t7 , $t4 , $t2 
 addiu   $t7 , $t4 , 3657177313 
 xor   $t0 , $t3 , $t2 
 
 # back to start of loop
 bnez $s4, main

 addiu $v0, $0, 10
 syscall

