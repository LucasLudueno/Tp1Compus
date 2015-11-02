#include <mips/regdef.h>

	.text
	.align 2
	.globl proximo
	.ent proximo
					  
proximo: 
		 subu sp,sp,8			# Genero el Stack
		 sw s8,4(sp)			# s8 = fp
		 sw gp,0(sp)		
		 move s8,sp
				
		 lw t0,24(sp)			# a0 = dir(a), a1 = i, a2 = j, a3 = regla, t0 = n
		 
		 mult a1,t0			
		 mflo t3		 		# 't3' = i*n	
		 
								# Calculo left
		 beq a2,zero,J_CERO		# Salto si j == 0									
		 subu t2,a2,1			# t2 = j-1
		 
REGRESO_J_CERO: 				# t2 = (n-1) o (j-1)
		 addu t5,t2,t3			# t5 = (i*n + n-1) o (i*n + j-1) 
		 addu t5,t5,a0			# t5 = (a + i*n + n-1) o (a + i*n + j-1)
		 lb t6,0(t5)			# 't6' = left (1 byte)
							
								# Calculo right
		 addu t5,a2,1			# t5 = j+1											
		 beq t0,t5,J_N			# Salto si j == n-1
		 addu t2,a2,1			# t2 = j+1
		 
REGRESO_J_N: 
		 addu t5,t2,t3			# t5 = (i*n + j+1) o (i*n)
		 addu t5,t5,a0			# t5 =  (a + i*n + j+1) o (a + i*n)
		 lb t7,0(t5)			# 't7' = right (1 byte)
		 
								# Calculo actual
		 addu t5,t3,a2			# t5 = n*i + j										
		 addu t5,t5,a0			# t5 = (a + i*n + j)
		 lb t5,0(t5)			# 't5' = actual				
						
								# Calculo pos en t0
		 sll t5,t5,1			# t5 = actual*2										
		 sll t6,t6,2			# t6 = left*4

		 addu t0,zero,t7		# t0 = right
		 addu t0,t0,t5			# t0 = right + actual*2
		 addu t0,t0,t6			# t0 = right + actual*2 + left*4 = pos
								
								# Calculo value en t7
		 addu t1,zero,31		# t1 = 31											
		 subu t2,t1,t0			# t2 = 31 - pos
		 sll t7,a3,t2			# regla << (31 - pos)
		 srl t7,t7,31			# t7 = value = regla >> 31		
		 
		 addu v0,zero,t7		# Devuelvo value
		
		 lw gp,0(s8)			# Regenero el Stack
		 lw s8,4(s8)
		 addu sp,sp,8
		
		 jr ra					# Vuelvo a Extend
	
J_CERO:
		subu t2,t0,1			# t2 = n - 1
		b REGRESO_J_CERO
			
J_N:
		addu t2,zero,zero		# t2 = 0
		b REGRESO_J_N
	
		.end proximo
