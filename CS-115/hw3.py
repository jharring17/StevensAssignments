############################################################
# Name: Jack Harrington
# CS115 HW3 ~ Applications of Map & Reduce
# Due : Sep. 30th, 2020
# 
# Pledge: I pledge my honor that I have abided by the Stevens Honor System. 
############################################################


# All functions should be written using map/reduce.
# No loops, no recursion, or other built-in functions unless explicitly allowed.
# You are free to write helper functions, so long as the main functions work as intended.

from functools import reduce
from math import factorial, sqrt # this import is necessary to use sqrt and factorial.

############################################################
#
#  taylorApproxE(lastIter):
#
#  Compute an approximation of e (the base of the natural logarithm),
#  using the taylor series of e^x (around 0) when x=1.
#
#  The approximation: e = 1 + 1 + 1/2 + 1/6 + 1/24 + 1/120 + ... + 1/r! + ...
#  where r! is the factorial function: r! = r * ... * 2 * 1
#
#  The input lastIter represents the iteration after which the (infinite) Taylor series
#  should be truncated, so lastIter=0 returns only the first term in the sum, lastIter=1
#  returns only after the first iteration has occured, (aka the first two terms), and so on.
#
#  Hint: Start with range(lastIter+1) to get the list [0, 1, ..., lastIter]
#
#  Assumptions: lastIter is an nonnegative integer
#
#  Allowed functions: range(), factorial()
#
#  Examples: taylorApproxE(4) = 2.708333333333333
#            taylorApproxE(1) = 2
#
############################################################

# Finds the Taylor Approximation for the inputted integer
def taylorApproxE(lastIter):
    
    # creates a variable lst to match user input for lastIter
    lst = range(lastIter + 1)

    # apllies the arithetic sequence in the lambda to the lst variable starting at array position 0
    solver = reduce(lambda x,y: x + 1 / factorial(y), lst, 0)
    return solver

############################################################
#
# vectorNorm(vect1):
#
# Compute the vector norm of a list, that is, the square-root of the
# sum of the squares of the list entries.
#
# Assumptions: vect1 is a nonempty array of numbers
#
# Allowed functions: sqrt()
#
# Examples: vectorNorm([3, 5, 11, 13]) = 18.0
#           vectorNorm([1, 1, 1]) = 1.7320508076
#
############################################################

# Finds the square root sum of squares
def vectorNorm(vect1):

    # apllies the arithmetic sequence in the lambda to the lst variable starting at array position 0
    solver = reduce(lambda x,y: x + (y*y), vect1, 0)

    # returns the square root of the sum of squares  
    return sqrt(solver)


############################################################
#
# arithMean(vect1):
#
# Compute the arithmetic mean of a list of numbers. The mean of a list
# is the sum of its elements divided by the length of the list.
#
# Assumptions: vect1 is a nonempty array of numbers
#
# Allowed functions: len()
#
# Example: arithMean([4, 1, 3, 6, 12]) = 5.2
#
############################################################

# Finds the mean value of the array 
def arithMean(vect1):

    # apllies the arithmetic sequence in the lambda to the lst variable starting at array position 0
    solver = reduce(lambda x,y: x + y, vect1, 0)

    # returns the value of solver divided by the length of array solver
    return solver / len(vect1)




