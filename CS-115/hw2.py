# Created by Prof. Nicolosi & Dominick DiMaggio for CS 115 at Stevens Institute of Technology, 2020

##########################################
# Name: Jack Harrington
# Pledge: I pledge my honor that I have abided by the Stevens Honor System. 
#
##########################################
from math import floor

######################################################################
# Task 1: Given an 8-digit decimal number representing the date,
#         calculate the day of the week
# Input: 8-digit decimal number in the format of YYYYMMDD
# Saturday: 0, Sunday: 1... Friday: 6  

def getWeekday(timestamp):
    day = timestamp % 100
    month = timestamp % 10000 // 100
    year_cent = timestamp // 10000 % 100
    cent_in_year = timestamp // 1000000

    day_of_week = ((day) + (((month + 1) * 26) / 10) + (year_cent) + (year_cent / 4) +
                   (cent_in_year / 4) - 2 * cent_in_year) % 7
    if day_of_week == 0:
        return 'Saturday'

    elif day_of_week == 1:
        return 'Sunday'

    elif day_of_week == 2:
        return 'Monday'

    elif day_of_week == 3:
        return 'Tuesday'

    elif day_of_week == 4:
        return 'Wednesday'

    elif day_of_week == 5:
        return 'Thursday'

    elif day_of_week == 6:
        return 'Friday'

    else:
        return 'Not a valid date. Try again.'


######################################################################
# Task 2: For this task, you will create an encoder and decoder
#         for a Caesar cipher using the map function.
# You may find this website helpful:
# https://cryptii.com/pipes/caesar-cipher

######################################################################
# This provided helper function may be useful
# Input: List of ASCII values (Ex: [72, 69, 76, 76, 79])
# Output: String (Ex. 'HELLO')     ('H   E   L   L   O')
def asciiToString(asciiList):
    return ''.join(map(chr, asciiList))


######################################################################
# Encoder
def caesarEncoder(str, shift):
    characters = list(str)
    lst = map(ord, characters)
    def caesar(num):
        return num + shift
    return asciiToString(map(caesar, lst))



######################################################################
# Decoder
# Input: A string value with all capital letters (leave everything
#        else as-is) and a shift value (Ex. KHOOR ZRUOG, 3)
# Output: A decoded string             (Ex. HELLO WORLD)
# Hint: The chr() function converts ASCII to a single-character string
def caesarDecoder(str, shift):
    def decode (num):
        return num - shift
    characters = list(str)
    lst = map(ord, characters)
    return asciiToString(map(decode, lst))
