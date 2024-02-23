# labwork.S
  # Written 2015 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1 2015-2016.
  # The macros PUSH and POP are in the public domain.

.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm

  # You can add your own code here
  #
.data
.text

.globl 	time2string
.globl 	delay 

hexasc: 
	andi	$a0, $a0, 0xf
	slti	$t0, $a0, 10 
	beq	$t0, $zero, else
	nop	
	addi	$v0, $a0, 48	
	jr 	$ra
	nop
		
else: 
	addi	$v0, $a0, 55	
	jr 	$ra
	nop
	
delay:
	addi	$t2, $0, 3815		# constant 
	
	while:
		slt	$t0, $zero, $a0		# if 0 < ms($a0) ---->  1, else 0
		beq 	$t0, $zero, end_while	# if $t0 == 0    ---->  end_while	
		nop
		addi	$a0, $a0, -1
		addi	$t1, $0, 0		# int i
		
		for:
			slt	$t0, $t1, $t2	# if $t1 < $t2	 ---->  1, else 0
			beq	$t0, $zero, while
			nop
			addi	$t1, $t1, 1
			j	for
			addi	$t1, $t1, 1	# (nop)
# less but not completely compliant the C code (constant != 0)
#			bne	$t1, $t2, for
#			addi	$t1, $t1, 1
#			j	while
#			nop			
	end_while:
	jr	$ra
	nop

save:	# use to save data to array
	sb	$v0, 0($s0)
	addi	$s0, $s0, 1
	jr 	$ra
	nop
	
time2string:

	PUSH	$ra#save $ra in stack
	PUSH	$s0
	#save ascii code for N in array arr
	move	$s0, $a0
	andi	$t1, $a1, 0xF000	#get N digit
	srl	$t1, $t1, 12
	move	$a0, $t1
	jal	hexasc	
	nop
	jal	save
	nop	
	#save ascii code for B in array arr		
	andi	$t1, $a1, 0x0F00	#get B digit
	srl	$t1, $t1, 8
	move	$a0, $t1
	jal	hexasc	
	nop
	jal	save
	nop
	#save ascii code for ':' in array arr
	addi	$v0, $0, 0x3A
	jal	save
	nop	
	#save ascii code for C in array arr
	andi	$t1, $a1, 0x00F0	#get C digit
	srl	$t1, $t1, 4
	move	$a0, $t1
	jal	hexasc	
	nop
	jal	save
	nop
	#save ascii code for D in array arr
	andi	$t1, $a1, 0x000F	#get D digit
	move	$a0, $t1
	jal	hexasc	
	nop
	jal	save
	nop
	#save ascii code for 'NUL' in array arr
	addi	$v0, $0, 0x00
	jal	save
	nop
	
	POP	$s0
	POP	$ra
	jr	$ra
	nop
