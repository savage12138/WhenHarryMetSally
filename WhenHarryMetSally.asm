#     When Harry Met Sally
#
# Author: Yida Wang	
# Last date modified: September 12th, 2019
#
#
# This program finds the earliest point at which Harry and Sally lived in the
# same city.
#
#  output register usage:
#  $2: earliest year in same city
#
	
.data
Harry:  .alloc  10            # allocate static space for 5 duration-city pairs
Sally:  .alloc  10            # allocate static space for 5 duration-city pairs

# R17: count
# R1: Harry
# R2: Answer
# R3: Verify Answer
# R4: location
# R5: answer
# R6: i
# R7: j
# R8: 1 or 0
# R9: 2
# R18: 4

.text
WhenMet:	addi    $1, $0, Harry   		# set memory base			
			# addi	$2, $0, -1				# DEBUG
        	swi     597             		# create timelines and store them
        	
			# Initialize variables
			addi	$17, $0,  1				# count = 1
			addi	$4,  $0,  4				# location = 4
			addi	$5,  $0,  0				# answer = 0
			addi	$6,  $0,  0				# i = 0
			addi	$7,  $0,  0				# j = 0
			addi	$9,  $0,  2				# store 2 in R9 as a multiplier
			addi	$18, $0,  4				# store 4 in R18 as a divider
			
			# Loop1
ForLoop1:	slti	$8,  $6,  20			# is i < 5?	
			beq		$8,	 $0,  NoAnswer		# if not, jump to NoAnswer
			mult	$6,	 $9	 				# i*2
			mflo	$10						# put i*2 in R10
			lw		$11, Harry($10)			# R11 = HarryTimeline[i*2]

			# Loop2
ForLoop2:	div		$7,	 $18				# calculate j instead of j * 4
			mflo	$19						# transfer to R19
			slt	 	$8,  $19, $11			# is j < HarryTimeline[i*2]
			beq		$8,  $0,  EndLoop1		# if not exit loop1

			# HarryTimeline[i*2+1]
			addi	$12, $10, 4				# R12 = i*2+1

			# check city indices
			lw		$13, Harry($12)			# R13 = HarryTimeline[i*2+1]
			lw 		$14, Sally($4)			# R14 = SallyTimeline[location]
			beq		$13, $14, Answer 		# R13 == R14? if equal jump to Answer

			# check if count reach cap year
			addi	$15, $4,  -4			# R15 = location-1, time index for Sally
			lw		$16, Sally($15)			# R16 = SallyTimeline[location-1]
			bne		$17, $16, IncCount		# is count == SallyTimeline[location-1]? if not, jump to IncCount
			addi	$17, $0,  1				# if they equal, count = 1;
			addi	$4,  $4,  8				# location = location + 8
			j IncAns						# jump to IncAns

IncCount:	addi	$17,  $17,  1			# count = count + 1
IncAns:		addi	$5,  $5,  1				# answer = answer + 1
Incj:		addi	$7,	 $7,  4				# j = j + 4
			j ForLoop2						# jump back to loop2

EndLoop1:	addi	$6,  $6,  4				# i = i + 4
			addi	$7,	 $0,  0				# reset j to 0
			j ForLoop1						# jump back to loop1

Answer:     addi    $2,  $5,  1990			# Year = 1990 + answer
			j End 							# jump to End
NoAnswer:	addi    $2,  $0,  0				# No answer
End:		swi     587						# Verify answer
            jr    	$31               		# return to caller
