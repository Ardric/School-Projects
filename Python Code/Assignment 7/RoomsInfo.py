#Daniel Lowdermilk

from RoomsFunctions import *

roomlist = [ {"number": 100, "name":"Jones Room", "sqft": 150, "seating": 9},
          {"number": 105, "name":"Smith Room", "sqft": 550, "seating": 50},
          {"number": 107, "sqft": 150, "seating": 12},
          {"number": 109, "name":"Thomas Room", "sqft": 200, "seating": 18},
          {"number": 111, "sqft": 150, "seating": 9},
          {"number": 115, "name":"Scott's closet", "sqft": 12}
          ]


print("How much total sq feet:" , totalSqFt(roomlist))
print("Largest room:" , numberOfLargestRoom(roomlist))
print("How many named" , howmanyNamed(roomlist))
print("How many total seats: " , totalSeats(roomlist))
