# Name: Jack Harrington
# Honor Pledge: I pledge my honor that i have abided by the Stevens Honor System.
#
#
##########################################################################################

from random import randrange


##########################################################################################
# Task #1: Change
# Takes user input for a change value and coin values.
# Returns the smallest number of coins needed to make the change.

def change (price, coins):
    if coins == []:
        return float('inf')
    elif price == 0:
        return 0
    elif price - coins[len(coins) - 1] >= 0:
        return min(1 + change(price - coins[len(coins) - 1], coins), change(price, coins[:len(coins) - 1]))
    else:
        return change(price, coins[:len(coins) - 1])


##########################################################################################
# Task #2: Currency
# Takes user input and creates a random array of the assigned length from the user

def currency (length):
    base = [*range(0, length)]
    lst = list(map(lambda x: x - x + randrange(length*2) + 1, base))

    def add (lst, max):
        num = randrange (max) + 1
        if num in lst:
            return add (lst, max)
        return num

    def noMult (max, lst, index):
        if index >= len (lst):
            return lst
        elif lst[index] in lst[:index] or lst[index] in lst[index + 1:]:
            lst = lst [:index] + lst [index + 1:]
            lst += [add (lst, max)]
            return noMult (max, lst, index + 1)
        else:
            return noMult (max, lst, index + 1)

    return noMult(length*2, lst, 0)


##########################################################################################
