#Daniel Lowdermilk

# returns the number of days above 90 degrees in the listOfDailyTemps
# listOfDailyTemps is a list of numbers, each representing the temperature 
# on a particular day
#  EG   daysAbove90([92,88,91,80,90,82,88])     should return 2
def daysAbove90(listOfDailyTemps):
    count = 0
    for x in listOfDailyTemps:
        if x > 90:
            count = count + 1
    return count



 

""""In this election season, consider tracking a donor via a tuple with the following format:
(name,  amount pledged, amount paid)
Write the function below.

Sample call:   
getGenerous ( [ (â€œJoeâ€,100,50),   (â€œMaryâ€,100,200),  (â€œTerryâ€,50, 75),
 		    (â€œChrisâ€,200,150), (â€œSkylerâ€, 500, 500), (â€œJodyâ€,400,500) ] )
should return:
 [  (â€œMaryâ€,100,200),  (â€œTerryâ€,50, 75),   (â€œJodyâ€,400,500) ] 

"""

# returns a list of all of the donors in the list who paid more than 
# he/she pledged.
def getGenerous(listOfDonors):
    newlist = []
    for x in listOfDonors:
        if x[2] > x[1]:
            newlist.append(x)
    return newlist



# returns a list of the NAMES of the donors in the list who paid more than 
# he/she pledged.
def getGenerousNames(listOfDonors):
    newlist = []
    for x in listOfDonors:
        if x[2] > x[1]:
            newlist.append(x[0])
    return newlist
