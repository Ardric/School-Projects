# a program for testing purpose.
# lack of documentation is intentional


from quizFunctions import *


def testDaysAbove90(temps):
    print(temps , " -> " , daysAbove90(temps))


def testGetGenerous(donors):
    print(donors)
    print("       Generous among them:")
    print("             ", getGenerous(donors))
    print("---")

def testGetGenerousNames(donors):
    print(donors)
    print("       Generous among them:")
    print("             ", getGenerousNames(donors))
    print("---")

###############################################
print ("Testing Days Above 90")

testDaysAbove90([92,88,91,80,90,82,88])
testDaysAbove90([])
testDaysAbove90([72,88,81,80,60,82,88,90])
testDaysAbove90([72,88,81,80,60,82,88,92])
testDaysAbove90([92,98,91,92,96,92,98,92])



print()
print ("Testing getGenerous:")
testGetGenerous( [ ("Joe",100,50),   ("Mary",100,200),  ("Terry",50, 75),
 		    ("Chris",200,150), ("Skyler", 500, 500), ("Jody",400,500) ] )
testGetGenerous( [ ("Jody",400,500), ("Joe",100,50),   ("Mary",100,200),  ("Terry",50, 75),
 		    ("Chris",200,150), ("Skyler", 500, 500)  ] )
testGetGenerous( [  ] )
testGetGenerous( [ ("Joe",100,50),   ("Mary",100,100),  ("Terry",50, 45),
 		    ("Chris",200,150), ("Skyler", 500, 400), ("Jody",400,400) ] )
testGetGenerous( [ ("Alex",200, 250), ("Joe",100,50),   ("Mary",100,200),  ("Terry",50, 75),
 		    ("Chris",200,150), ("Skyler", 500, 500), ("Jody",400,500),
                   ("Bernie",50,50), ("Jordan",100, 150)] )

print()
print ("Testing getGenerousNames:")
testGetGenerousNames( [ ("Joe",100,50),   ("Mary",100,200),  ("Terry",50, 75),
 		    ("Chris",200,150), ("Skyler", 500, 500), ("Jody",400,500) ] )
testGetGenerousNames( [ ("Jody",400,500), ("Joe",100,50),   ("Mary",100,200),  ("Terry",50, 75),
 		    ("Chris",200,150), ("Skyler", 500, 500)  ] )
testGetGenerousNames( [  ] )
testGetGenerousNames( [ ("Joe",100,50),   ("Mary",100,100),  ("Terry",50, 45),
 		    ("Chris",200,150), ("Skyler", 500, 400), ("Jody",400,400) ] )
testGetGenerousNames( [ ("Alex",200, 250), ("Joe",100,50),   ("Mary",100,200),  ("Terry",50, 75),
 		    ("Chris",200,150), ("Skyler", 500, 500), ("Jody",400,500),
                   ("Bernie",50,50), ("Jordan",100, 150)] )
