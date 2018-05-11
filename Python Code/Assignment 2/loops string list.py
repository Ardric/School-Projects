#Daniel Lowdermilk
#This program does basic list manipulation on strings to tell you the total numbers of characters in all strings,
#tells you the length of the longest word, tells you the amount of words that start with a vowel and tells you how
#many words have more than 5 characters.

#Default variables
nameList = ["Huey", "Dewey", "Louie", "Rumpelstiltskin", "Mickey", "Minnie", "Donald"
            "Daffy", "Bugs", "Yosemite Sam", "Elmer Fudd"]
long_str = 0
length = 0
num_chars = 0
num_vowels = 0

for x in nameList:
    if len(x) > 5:
        long_str = long_str + 1
    if len(x) > length:
        length = len(x)
    if x[:1] == "a" or x[:1] == "e" or x[:1] == "i" or x[:1] == "o" or x[:1] == "u" or x[:1] == "A" or x[:1] == "E" or x[:1] == "I" or x[:1] == "O" or x[:1] == "U":
        num_vowels = num_vowels + 1
    num_chars = num_chars + len(x)
print ("Total number of characters entered: ", num_chars)
print ("Length of the longest word: ", length)
print ("Number of words that started with a vowel: ", num_vowels)
print ("Number of strings longer than length 5: ", long_str)
