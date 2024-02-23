  # hexmain.asm
  # Written 2015-09-04 by F Lundevall
  # Copyright abandonded - this file is in the public domain.

	.text
main:
	li	$a0,9		# change this to test different values

	jal	hexasc		# call hexasc
	nop			# delay slot filler (just in case)	

	move	$a0,$v0		# copy return value to argument register

	li	$v0,11		# syscall with v0 = 11 will print out
	syscall			# one byte from a0 to the Run I/O window
	
stop:	j	stop		# stop after one run
	nop			# delay slot filler (just in case)

  # You can write your own code for hexasc here
  #
hexasc: 
	andi	$a0, $a0, 0xf	# mask bit 3:0
	slti	$t0, $a0, 10	# if t0 < 10 --> t0 = 1, else t0 = 0
	beq	$t0, $zero, else
	nop	
	addi	$v0, $a0, 48	
	jr 	$ra
	nop
		
else: 
	addi	$v0, $a0, 55	
	jr 	$ra
	nop
	
	

