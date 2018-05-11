#Daniel Lowdermilk
#This takes your annual salary and multiplies it by your appropriate tax amount and outputs your tax.
Income = input("Enter your yearly salary: ")
if int(Income) < 11000:
    Tax = int(Income) * .03
if int(Income) < 21000:
    Tax = int(Income) * .07
if int(Income) < 31000:
    Tax = int(Income) * .10
if int(Income) >= 31000:
    Tax = int(Income) * .25
print("Your income tax is: ", int(Tax))
