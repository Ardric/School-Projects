#Daniel Lowdermilk
#This takes a phone number and puts it into the proper format by using correct formatting in the print
#statement when selecting substrings.
Number = input("Please enter you phone number in the following format ##########: ")
String = str(Number)
print('Proper Formatting: ({}) {}-{}'.format(String[:3], String[3:-4], String[-4:]))

