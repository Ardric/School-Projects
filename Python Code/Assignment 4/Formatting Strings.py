#Daniel Lowdermilk

#Uses a lot of the same code as the previous banking problem to get and parse banking information.  Then
#just opens a new file and reformats the information in a more readable way.

textfile = input("Please enter the name of a file with bank account information: ")
f = open(textfile, 'r')
f_new = open('Formatted Information.txt', 'w')
unformated_info = f.readlines()
for i in unformated_info:
    acct_info = i.split()
    for i in acct_info:
        acct_info = i.split(',')
        f_new.write('There is a balance of $')
        f_new.write(acct_info[1])
        f_new.write(' in account# ')
        f_new.write(acct_info[0])
        f_new.write(".\n")
f.close()
f_new.close()
