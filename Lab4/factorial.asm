.text

	addi	$a0, $0, 3	# imm = n
	addi	$v0, $0, 1	# set v0 to 1
	addi	$v1, $0, 1	# set v1 to 1
	addi	$a1, $0, 0	# a1 = int i in loop
	beq	$a0, $0, done	# if n == 0  --> done
	add	$0, $0, $0	# nop
# C code of forI and forJ
#int factorial(int n){
#int factor(int n){
#    int v0 = 1;
#    int v1;
#    for (int i = 1; i < n ; i++)	// 1, 2, 3, .... n-1, n
#    {
#        for (int j = 0; j < i; j++)
#        {
#            v1 += v0;   // v1 = (i-1)! * i = i!
#        }  
#        v0 = v1;    //v0 = i!
#    }
#    return v0;
#}
forI:
	add	$v0, $v1, $0	# move $v1 --> $v0
	addi	$a1, $a1, 1	# i++ (forI)
	add	$a2, $0, $0	# reset a2 to 0(int j in loop)
	beq	$a0, $a1, done	# if i == n --> done
	add	$0, $0, $0	# nop
	beq	$0, $0, forJ	# jump to do j loop
	add	$0, $0, $0	# nop

forJ:
	beq	$a1, $a2, forI	# if j == i --> forI
	add	$0, $0, $0	# nop
	add	$v1, $v1, $v0	# v1 = (i-1)! * i	
	addi	$a2, $a2, 1	# j++
	beq	$0, $0, forJ	# jump to forJ
	add	$0, $0, $0	# nop
	
done:
	add	$0, $0, $0	# nop
	beq	$0, $0, done	# infinity loop	
	add	$0, $0, $0	# nop
