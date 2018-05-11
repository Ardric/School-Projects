#Daniel Lowdermilk
#Reads in 10 numbers typed by the user and gives you the highest number typed with a for loop.
#Collaborated with Nick Keithley
num_list = []
y = 10
print ("Please input", y, "numbers, 1 at a time.")
for x in range(0,y) :
    num_list.append(int(input("Please enter a number: ")))
print ("The largest value you entered was: ", max(num_list))
