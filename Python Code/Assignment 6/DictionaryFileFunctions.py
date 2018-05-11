#Daniel Lowdermilk

# returns a list of all of the words in the text file
# assumes the file has one word per line.
def getWordList(filename):
    newlist = []
    fp = open(filename, 'r')
    words = fp.readlines()
    for x in words:
        newlist.append(x[:-1])
    fp.close()
    return newlist


# returns a list of all of the words in the list that meet the following criteria:
# - has 6 characters
# - has an "e" as the 2nd, 4th, and 6th characters.
#   EG   "redeye"
def getInterestingWords(listOfWords):
    newlist = []
    for x in listOfWords:
        if x[1] == 'e' and x[3] == 'e' and x[5] == 'e' and len(x) == 6:
                newlist.append(x)
    return newlist

# returns a list of all of the words in the list that alternate vowels and consonants.
#   EG   "redeye",  "atop", "became", "aloha"
def getReallyInterestingWords(listOfWords):
    newlist = []
    temp = ""
    for x in listOfWords:
        i = 0
        count = 0
        z = ''
        for y in x:
            if count > 0:
                if z == 'a' or z == 'e' or z == 'i' or z == 'o' or z == 'u':
                    if y != 'a' and y != 'e' and y != 'i' and y != 'o' and y != 'u':
                        temp = temp
                    else:
                        i = 1
                if z != 'a' and z != 'e' and z != 'i' and z != 'o' and z != 'u':
                    if y == 'a' or y == 'e' or y == 'i' or y == 'o' or y == 'u':
                        temp = temp
                    else:
                        i = 1
            count = count + 1
            z = y
        if i == 0:
            newlist.append(x)
    return newlist



# takes a list of words and displays to the screen pairs consisting
# of an "interesting" word and a "Really interesting" word.
# EG:   ("redeye", "aloha")
#       ("delete", "atop")
# FURTHER, the program displays the pairs one pair per line, and
#    pauses every 20 pairs, waiting for the user to hit <enter> before
#    continuing to the next pair

def displayPairsOfInterest(interesting, really_interesting):    
    pairs_of_interest = []   
    for x,y in zip(interesting, really_interesting):
        string = (x, y)
        pairs_of_interest.append(string)
        
    count = 0
    
    for x in pairs_of_interest:
        if count > 19:
            count = 0
            input("Press Enter to continue...")
        print(x)
        count = count + 1
    return pairs_of_interest


# write pairs of interest (as defined above) to the file with the given filename
def writePairsOfInterest(filename, listOfWords):
    tups = ""
    f = open(filename, 'w')
    for x in listOfWords:
        tups = str(x)
        f.write(tups)
        f.write("\n")
    f.close()
    return None
