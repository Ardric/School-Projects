#Daniel Lowdermilk

#in this file, a single room is identifed by a dictionary with possible keys:
# "number", "name", "sqft", and "seating"

########################
# return the total number of sq ft in the building
# assume every room has a sq ft attached to it
def totalSqFt(roomlist):
    total_sq_ft = 0
    for dictionary in roomlist:
        for key, value in dictionary.items():
                if key == "sqft": 
                    total_sq_ft = total_sq_ft + value
    return total_sq_ft


############################
# return the number of the room witht he largest sq ft
# break ties as you see fit
# assume every room has a sq ft attached to it

def numberOfLargestRoom(roomlist):
    largest_sq_ft = 0
    for dictionary in roomlist:
        for key, value in dictionary.items():
            if key == "sqft":
                if value > largest_sq_ft:
                    largest_sq_ft = value
                else:
                    continue
    return largest_sq_ft

###################################
# returns how many of the rooms have a "name" attached to them
def howmanyNamed(roomlist):
    number_of_names = 0
    for dictionary in roomlist:
        for key, value in dictionary.items():
            if key == "name":
                if value != "":
                    number_of_names = number_of_names + 1
                else:
                    continue
    return number_of_names


##########################
# return the total number of seats in the building
# If a room does not have a number of seats listed, assume it is 0
def totalSeats(roomlist):
    number_of_seats = 0
    for dictionary in roomlist:
        for key, value in dictionary.items():
            if key == "seating":
                number_of_seats = number_of_seats + value
            else:
                continue
    return number_of_seats
