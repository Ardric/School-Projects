# a program for testing purpose.
# lack of documentation is intentional

from StudentListFunctions import *

def testUniqueChar(alist):
    print(alist , " ---> " , uniqueCharacterStrings(alist))

def testOldestPerson(alist):
    print(alist , " ---> " , oldestPerson(alist))

def testEyeColor(alist,color):
        print(alist , " and " , color , " ---> " , howManyEyesThisColor(alist,color))

def testCross(list1,list2):
        print(list1,"\n",list2,"\n","result: ", cross(list1,list2))
              

print("Testing Unique Char Strings:")
testUniqueChar(["hello","bye","apple","peach","banana"])
testUniqueChar(["a","aa","b","bbbb","bced"])
testUniqueChar(["Monday","Friday","Sunday","Tuesday","Thursday"])

print()
print("Testing Oldest Person:")
testOldestPerson([ ("Mary",17,"green"), ("Joe",42,"blue"),   ("Anne", 31, "brown") ])
testOldestPerson([ ("Mary",17,"green"), ("Joe",42,"blue"),   ("Anne", 31, "brown"),("Tom",24,"blue") ])
testOldestPerson([ ("Anne", 31, "brown"), ("Mary",17,"green"), ("Joe",42,"blue"),  ("Terry",45,"brown"),  ("Tom",24,"blue") ])

print()
print ("Testing eye color" )
testEyeColor([ ("Mary",17,"green"), ("Joe",42,"blue"),   ("Anne", 31, "brown") ],  "blue")
testEyeColor([ ("Mary",17,"green"), ("Joe",42,"blue"),   ("Anne", 31, "brown"),("Tom",24,"blue") ], "blue")
testEyeColor([ ("Anne", 31, "brown"), ("Mary",17,"green"), ("Joe",42,"blue"),  ("Terry",45,"brown"),  ("Tom",24,"blue") ], "blue")
testEyeColor([ ("Anne", 31, "brown"), ("Mary",17,"green"), ("Joe",42,"blue"),  ("Terry",45,"brown"),  ("Tom",24,"blue") ], "brown")

print()
print ("Testing cross" )
testCross( ["Joe", "Terry", "Chris"], [ 4, 7, 9, 8])
testCross( [ 4, 7, 9, 8], ["Joe", "Terry", "Chris"] )
testCross( ["Pepperoni","Sausage"], ["Small","Medium","Large"])
