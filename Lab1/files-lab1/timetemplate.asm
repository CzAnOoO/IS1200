  # timetemplate.asm
  # Written 2015 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

.macro	PUSH (%reg)
	addi	$sp,$sp,-4
	sw	%reg,0($sp)
.end_macro

.macro	POP (%reg)
	lw	%reg,0($sp)
	addi	$sp,$sp,4
.end_macro

	.data
	.align 2
#	arr: .space 6	creat array
mytime:	.word 0x5957
timstr:	.ascii "text more text lots of text\n"
	.text	
main:
	# print timstr
	la	$a0,timstr
	li	$v0,4
	syscall
	nop
	# wait a little
	li	$a0,2
	jal	delay 
	# call tick
	la	$a0,mytime
	jal	tick
	nop
	# call your function time2string
	la	$a0,timstr
	la	$t0,mytime
	lw	$a1,0($t0)
	jal	time2string
	nop
	# print a newline
	li	$a0,10
	li	$v0,11
	syscall
	nop
	# go back and do it all again
	j	main
	nop
# tick: update time pointed to by $a0
tick:	lw	$t0,0($a0)	# get time
	addiu	$t0,$t0,1	# increase
	andi	$t1,$t0,0xf	# check lowest digit
	sltiu	$t2,$t1,0xa	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x6	# adjust lowest digit
	andi	$t1,$t0,0xf0	# check next digit
	sltiu	$t2,$t1,0x60	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa0	# adjust digit
	andi	$t1,$t0,0xf00	# check minute digit
	sltiu	$t2,$t1,0xa00	# if digit < a, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0x600	# adjust digit
	andi	$t1,$t0,0xf000	# check last digit
	sltiu	$t2,$t1,0x6000	# if digit < 6, okay
	bnez	$t2,tiend
	nop
	addiu	$t0,$t0,0xa000	# adjust last digit
tiend:	sw	$t0,0($a0)	# save updated result
	jr	$ra		# return
	nop

  # you can write your code for subroutine "hexasc" below this line
  #
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
		
delay:		# int ms
	addi	$t2, $0, 30000		# constant 
	
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
			nop
# less but not completely compliant the C code (constant != 0)
#			bne	$t1, $t2, for
#			addi	$t1, $t1, 1
#			j	while
#			nop
			
	end_while:
	jr	$ra
	nop

save:	# use to save data in to array
	sb	$v0, 0($s0)
	addi	$s0, $s0, 1
	jr 	$ra
	nop
	
time2string:

	PUSH	($ra)	#save $ra in stack
	PUSH	($s0)
#	PUSH	($s1)
	#save ascii code for N in array arr
	move	$s0, $a0
	andi	$t1, $a1, 0xf000	#get N digit
	srl	$t1, $t1, 12
	move	$a0, $t1
	jal	hexasc	
	nop
	jal	save
	nop	
	#save ascii code for B in array arr		
	andi	$t1, $a1, 0x0f00	#get B digit
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
	andi	$t1, $a1, 0x00f0	#get C digit
	srl	$t1, $t1, 4
	move	$a0, $t1
	jal	hexasc	
	nop
	jal	save
	nop
	#save ascii code for D in array arr
	andi	$t1, $a1, 0x000f#get D digit
	move	$a0, $t1
#	move	$s1, $t1
	jal	hexasc	
	nop
	jal	save
	nop
	
	#suprise assignment
	isOdd:		
		and $t2, $a0, 0x1	# mask first bit of "digit D" (Parity bit) 
		beq $t2, $zero, even	
		nop		
		odd:
			addi	$v0, $zero, 0x44
			j	out
			nop			
		even:				
			addi	$v0, $zero, 0x45
			j	out
			nop
	out:
	jal	save
	nop
	
	#save ascii code for 'NUL' in array arr
	addi	$v0, $0, 0x00
	jal	save
	nop
	
	#	
#	POP	($s1)
	POP	($s0)
	POP	($ra)
	jr	$ra
	nop			
