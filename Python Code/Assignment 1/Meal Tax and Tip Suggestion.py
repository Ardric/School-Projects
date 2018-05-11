#Daniel Lowdermilk
#Suggested Tip applied to meal cost + tax
#Calculates your tip amount based on the cost of your meal.
COM = input("Cost of Meal: ")
Tax = float(COM)* .053
Meal = float(COM) + float(Tax)
print("Amount of tax applied: ", float(Tax))
print("Suggested Tip amounts calculated with Meal cost + Tax amount.")
print("Tip Suggestions 15%: ", float(Meal) * .15)
print("Tip Suggestions 18%: ", float(Meal) * .18)
print("Tip Suggestions 20%: ", float(Meal) * .20)
