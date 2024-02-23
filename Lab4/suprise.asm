.text
	addi	$a0, $0, 9	# imm = n
	addi	$v0, $0, 1	# output
	addi	$a1, $0, 1	# int i = 0
forI:
	# n! = 1 * 2 * 3 * ... * n-1 * n
	#    = 1 * n * n-1 * ... * 3 * 2 * 1
	beq	$a0, $a1, done
	mul	$v0, $v0, $a0
	addi	$a0, $a0, -1
	beq	$0, $0, forI
	add	$0, $0, $0	# nop
	
done:
	beq	$0, $0, done
	add	$0, $0, $0	# nop
