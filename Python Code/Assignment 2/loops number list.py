#Daniel Lowdermilk
#This program does basic list manipulation to tell you what the average of the list is
#how many odd / even numbers are in the list, and tells you the max number in the list.

#Default varibles
numList = [45, 60, -2, 90, 87, 6, 5, 12, 14, -14, 9, 102, 41, 62]
total = 0
average = 0
nums_even = 0
nums_odd = 0
count = 0

for x in numList:
    total = x + total
    if x % 2 == 0:
        nums_even = nums_even + 1
    else:
        nums_odd = nums_odd + 1
    count = count + 1
average = total / count
print ("There are", nums_even,"even numbers.")
print ("There are", nums_odd,"odd numbers.")
print ("The average of the numbers are: ", average)
print ("The maximum number in the list is: ", max(numList))
        
