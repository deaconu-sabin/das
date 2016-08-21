#!/usr/bin/python

import random

#########################################################################
# Generate data like [ x, y, z] [ val = (c1*x + c2*y + c3*z + noise) ]  #
# where x,y,z are random numbers and c1, c2, c3 are coefficients(known) #
#########################################################################
coefficients = [2, 4, 7]

minRandom = -50;
maxRandom = 50;

# random.gauss(mean, sigma)
# first param is mean, 
# second param is standard deviation
noise = random.gauss(0, 10) 

inputs = []
output = 0
for index in range( len(coefficients) ):
	randFloat = random.uniform(minRandom, maxRandom)
	inputs.append( float(format(randFloat,'.3f')) )
	output += inputs[index] * coefficients[index]


output += float(format(noise,'.3f'))
print inputs , "[", output, "]"
