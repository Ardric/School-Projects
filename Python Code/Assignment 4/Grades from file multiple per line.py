#Daniel Lowdermilk

#This program takes a textfile entered by the user that contains numerical grades
#and calculates the average of the scores while also telling you the letter grade
#amounts of each score.

#Default Variables
grade = 0
sum_of_grades = 0
totalamount_of_grades = 0

#Grades
A = 0
B = 0
C = 0
D = 0
F = 0

textfile = input("Please enter the name of your grades textfile: ")
f = open(textfile, 'r')
grade = f.readlines()
for i in grade :
    gradelist = i.split()
    for y in gradelist :      
        x = int(y)
        if x < 60:
            F = F + 1
            sum_of_grades = sum_of_grades + x
            totalamount_of_grades = totalamount_of_grades + 1
        elif x > 59.9 and x < 70:
            D = D + 1
            sum_of_grades = sum_of_grades + x
            totalamount_of_grades = totalamount_of_grades + 1
        elif x > 69.9 and x < 80:
            C = C + 1
            sum_of_grades = sum_of_grades + x
            totalamount_of_grades = totalamount_of_grades + 1
        elif x > 79.9 and x < 90:
            B = B + 1
            sum_of_grades = sum_of_grades + x
            totalamount_of_grades = totalamount_of_grades + 1
        elif x > 89.9 and x <= 100:
            A = A + 1
            sum_of_grades = sum_of_grades + x
            totalamount_of_grades = totalamount_of_grades + 1
        elif x < 0 and x > 100:
            print("Invalid grade.")
        
average = sum_of_grades / totalamount_of_grades
print("There are", A, "A's.")
print("There are", B, "B's.")
print("There are", C, "C's.")
print("There are", D, "D's.")
print("There are", F, "F's.")
print("The average grade is:", average)

f.close()   
