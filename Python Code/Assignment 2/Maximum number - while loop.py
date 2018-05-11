#Daniel Lowdermilk
#Reads in 10 numbers typed by the user and gives you the highest number typed with a while loop.
#Collaborated with Nick Keithley
num_list = []
count = 0
y = 10
print ("Please input", y, "numbers, 1 at a time.")
while count < y :
    num_list.append(int(input("Please enter a number: ")))
    count = count + 1
print ("The largest value you entered was: ", max(num_list))
