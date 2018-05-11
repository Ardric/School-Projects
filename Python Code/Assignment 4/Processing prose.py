#Daniel Lowdermilk

#This program reads in a Prose from a textfile and parses the string / list read in to calculate how many lines were read in, the total number
#of characters, the total number of aplhabetic characters, the length of the longest word, the longest word, and how many vowels appear in the
#text.

#The tie breaker of the longest word is just whatever word comes first.

#Default Variables
line_count = 0
character_count = 0
alpha_char_count = 0
max_word = 0
longest_word = ""
vowels = 0

textfile = input("Please enter the name of a text file containing prose: ")
f = open(textfile, 'r')
block_quote = f.read()
character_count = len(block_quote[:-1])
for c in block_quote:
    if c == 'A' or c == 'a' or c == 'E' or c == 'e' or c == 'I' or c == 'i' or c == 'O' or c == 'o' or c == 'U' or c == 'u':
        vowels = vowels + 1
f.close()

f = open(textfile, 'r')
unformated_info = f.readlines()
for i in unformated_info:
    prose_info = i.split()
    for i in prose_info:
        prose_info = i.split(',')
        for i in prose_info:
            prose_info = i.split('.')
            for i in prose_info:
                prose_info = i.split('?')
                for i in prose_info:
                    prose_info = i.split('!')
                    for i in prose_info:
                        prose_info = i.split('"')
                        for i in prose_info:
                            prose_info = i.split(':')
                            for i in prose_info:
                                alpha_char_count = alpha_char_count + sum([len(i) for i in prose_info])
                                if max_word < len(i):
                                    max_word = len(i)
                                    longest_word = i
        
    print(i)
    line_count = line_count + 1
   

print("Total number of lines in file:", line_count)
print("Total number of characters in the file is:", character_count)
print("Total number of alphabetic characters with no whitespace or characters:", alpha_char_count)
print("The longest word length is:", max_word)
print("The longest word is:", longest_word)
print("There are", vowels, "vowels in the prose.")

f.close()

        
