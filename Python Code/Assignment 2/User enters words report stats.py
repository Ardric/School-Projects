#Daniel Lowdermilk
#This takes words entered by the user and tells you which word is the longest,
#what the total number of letters are in all words entered combined and what
#the longest word was.  It does this through if statement checks when reading
#the word in.

#Default variables
x = ""
longest_word = ""
length = 0
num_chars = 0

print ("When you are finished entering words, please enter '!!!'.")
while x != "!!!" :
    x = input("Please enter a word: ")
    if x == "!!!":
        break
    if len(x)> length:
        length = len(x)
        longest_word = str(x)
    num_chars = num_chars + len(x)
print ("Total number of characters entered: ", num_chars)
print ("Length of the longest word: ", length)
print ("The longest word entered was: ", longest_word)
    
