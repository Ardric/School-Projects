#Daniel Lowdermilk
#Calculates your cost of gas for a trip by multiplying the length of the trip
#by the cost per gallon then dividing that by your mile per gallon.
Length = input("Length: ")
MPG = input("MPG: ")
CPG = input("Cost Per Gallon: ")
print("Cost for Trip: ",(int(Length)*float(CPG))/int(MPG))
