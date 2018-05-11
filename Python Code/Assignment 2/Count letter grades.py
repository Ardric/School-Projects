#Daniel Lowdermilk
#This program reads in 10 numbers and calculates grades and reports how many of each grade is entered.
#If you change y in default variables, you change the amount of grades the instructor can enter.

#Default Variables
y = 10
grade = 0
#Grades
A = 0
B = 0
C = 0
D = 0
F = 0

print ("Please input", y, "numbers, 1 at a time.")
for x in range(0,y) :
    grade = int(input("Please enter a number: "))
    if grade < 60:
        F = F + 1
    elif grade > 59.9 and grade < 70:
        D = D + 1
    elif grade > 69.9 and grade < 80:
        C = C + 1
    elif grade > 79.9 and grade < 90:
        B = B + 1
    elif grade > 89.9 and grade <= 100:
        A = A + 1
    elif grade < 0 and grade > 100:
        print("Invalid grade.")
print("There are", A, "A's.")
print("There are", B, "B's.")
print("There are", C, "C's.")
print("There are", D, "D's.")
print("There are", F, "F's.")
    
    
