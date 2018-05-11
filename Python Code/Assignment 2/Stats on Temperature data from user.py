#Daniel Lowdermilk
#This program takes input from the user until they either type done or enter 10 temperatures
#below 32.  It then tells you the average of all temperatures, the max temp, the min temp,
#how many were above 90 and how many were below 32.



#Default Variables
x = ""
y = 0
low = 100
high = 0
count_high = 0
count_low = 0
count = 0
z = 0

print ("Please input temperatures, the program will stop either when you enter 10 numbers below 32 or when you type done.")
while x != "done" :
    x = input("Please enter a number: ")
    if x == "done":
        break
    count = count + 1
    y = int(x)
    z = z + y
    if y < low :
        low = y
    if y > high :
        high = y
    if y > 90 :
        count_high = count_high + 1
    if y < 32 :
        count_low = count_low + 1
        if count_low == 10:
            break
    
average = z / count
print ("The average of all temperatures that were entered is: ", average)
print ("The minimum temperature entered was: ", low)
print ("The highest temperature entered was: ", high)
print ("There were", count_high, "temperatures above 90.")
print ("There were", count_low, "temperatures below 32.")


    
    
