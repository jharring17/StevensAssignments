#
# 20fa-cs115bc
#
# Antonio R. Nicolosi 
# 20201120
#************************************************************
# *  Name  : Jack Harrinton
# * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
#************************************************************

# Programming problems with one-dimensional arrays.
def isWithinRange(arr, min, sup):
    """
     Return True if and only if all entries in the array fall between
     the specified values, with min being permitted but sup being just
     beyond the allowable range).
     
     Sample input/outputs:
     Let arr = [3, -5,  7, -1, -8, 0, -6, -2]
     Then:
	 * isWithinRange(arr, -6, 10) -> False;
	 * isWithinRange(arr, -8, 10) -> True;
	 * isWithinRange(arr, -8, 7)  -> False;
	 */
    """
    for i in range(len(arr)):
        if arr[i] < min or arr[i] >= sup:
            return False
        return True


def isPermutation(arr):
    """Returns True if and only if its entries, taken as a set, consist
    of all the numbers between 0 and len(arr)-1 (possibly permuted
    according to some arbitrary order).

    Sample input/outputs:
    * isPermutation([3, -5, 7, 4, -1, -8, 0, -6, -2]) --> False
    * isPermutation([3, 5, 7, 4, 1, 8, 0, 6, 2])      --> True
    * isPermutation([3, 1, 0, 3, 0])                  --> False
    * isPermutation([])                               --> True
    """
    if arr == []:
        return True
    nums = [*range(len(arr))]
    for i in range(len(arr)):
        if arr[i] < 0 or arr[i] > len(arr) - 1:
            return False
        nums[arr[i] - 1] = 0
    for i in range(len(nums)):
        if nums[i] != 0:
            return False
    return True

def isCyclic(arr):
    """
    Return true if-and-only-if the sequence arr[0], * arr[arr[0]],
    arr[arr[arr[0]]], ... reaches 0 * after traversing all entries in
    arr.

    Sample input/outputs:
    * isCyclic([3, 5, 7, 4, 1, 8, 0, 6, 2)] --> True
    * isCyclic([3, 5, 7, 4, 1, 8, 6, 0, 2]) --> False
    * isCyclic([3, 1, 0, 3, 0])             --> False
    * isCyclic([])                          --> True
    """
    if arr == []:
        return True
    ind = arr[0]
    for i in range(1, len(arr)):
        ind = arr[ind]
    if ind == 0:
        return True
    return False

def isSloppilySorted(arr, k):
    """
    Return True if-and-only-if the entries in arr are sorted sloppily 
    "up to k", that is, every entry precedes at most k smaller values
     and follows at most k larger values.

    Sample input/outputs:
    * isSloppilySorted([3, 2, 1, 0, 4, 8, 7, 6, 5], 3) --> True
    * isSloppilySorted([3, 2, 1, 0, 4, 8, 7, 6, 5], 2) --> False
    * isSloppilySorted([0, 1, 2, 3, 4, 5, 6, 7, 8], 1) --> True
    * isSloppilySorted([], 3)                          --> True
    """
    for i in range(len(arr)):
        num = 0
        tail = arr[:i]
        head = arr[i + 1:]

        for x in range(len(tail)):
            if tail [x] > arr[i]:
                num += 1
            if num > k:
                return False
        num = 0

        for x in range(len(head)):
            if head[x] < arr[i]:
                num += 1
            if num > k:
                return False
    return True
