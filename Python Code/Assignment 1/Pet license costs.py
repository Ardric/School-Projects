#Daniel Lowdermilk
#Calculates how much you have to pay for collars based on the amount of pets you have.
num_cats = input("How many Cats do you own?: ")
num_dogs = input("How many Dogs do you own?: ")
if int(num_cats) > 5:
    price_cats = int(num_cats) * 6
else:
    price_cats = int(num_cats) * 7
price_dogs = int(num_dogs) * 8
print("Total for cat licenses: ", int(price_cats))
print("Total for dog licenses: ", int(price_dogs))
