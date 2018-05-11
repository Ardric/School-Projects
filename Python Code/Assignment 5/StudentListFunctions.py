#Worked on the first 3 with Nick Keithly
###################
# return a list of all of the strings in the argument that do not
# have any duplicate letters in them.
# EG:  ["hello","bye","apple","peach","banana"]
# should return
#      ["bye","peach"]
def uniqueCharacterStrings(words):
    final_list = []
    list(words)
    for x in words:
        length = len(x)
        y = len(set(x))
        if y == length:
            final_list.append(x)         
    return final_list


######################################
# the following two functions assume a person is represented by a tuple
# of the form   (name, age, eye color)


######################
# return how many of the people in the list have the given eye color
# EG: [("Mary",17,"green"), ("Joe",42,"blue"),   ("Anne", 31, "brown"),("Tom",24,"blue") ]
# and "blue" should return 2
def howManyEyesThisColor(people,color):
    count = 0
    for x in people:
        if x[2] == color:
            count = count + 1
    return count



######################################
# return the name of the oldest person in the list.  (break ties as you see fit)
# EG[ ("Mary",17,"green"), ("Joe",42,"blue"),   ("Anne", 31, "brown") ]
# should return "Joe"
def oldestPerson(people):
    age = 0
    for x in people:
        if x[1] > age:
            age = x[1]
            name = x[0]
    return name


######################################
# return a list that is the "cross" of the two given lists, with a tuple for each pair.
# EG  ["Joe", "Terry", "Chris"]   and [ 4, 7, 9, 8]
# should return:
#  [("Joe",4),("Joe",7),("Joe",9),("Joe",8),("Terry",4),("Terry",7),("Terry",9),("Terry",8),
#             ("Chris",4),("Chris",7),("Chris",9),("Chris",8)]

def cross(list1, list2):
    newlist = []
    for x in list1:
        for y in list2:
            tup = (x, y)
            newlist.append(tup)
    return newlist
