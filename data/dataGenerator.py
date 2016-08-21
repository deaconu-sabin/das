#!/usr/bin/python

import random

############################################################
# Generate data like [ a, b, c] [2*a + 4*b + 6*c + noise]  #
############################################################

coefficients = [2, 4, 6]

# random.gauss(mean, sigma)
# first param is mean, 
# second param is standard deviation
noise = random.gauss(0, 0.5) 

inputs = []
output = 0
for index in range( len(coefficients) ):
	randFloat = random.uniform(-5, 5)
	inputs.append( float(format(randFloat,'.3f')) )
	output += inputs[index] * coefficients[index]


output += float(format(noise,'.3f'))
print inputs , "[", output, "]"
