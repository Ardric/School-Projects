#Daniel Lowdermilk

#This program takes in a text file filled with bank account information
#and prints out: # of accounts, average account balance, sum of account
#balances, maximum balance, and the number of accounts with over $100.

#As an error check, if an account has a negative balance, the program
#will alert the user that a account has a negative balance and will exit
#the program. Just wanted a simple way to handle a negative balance.  This
#is not the appropriate way to handle this but is something for now.

#Default Variables
avg_acct_bal = 0
total_num_accts = 0
sum_of_accts = 0
max_account = 0
value_accts = 0

textfile = input("Please enter the name of a file with bank account information: ")
f = open(textfile, 'r')
f_low = open('lowbalance.txt', 'w')
unformated_info = f.readlines()
for i in unformated_info:
    acct_info = i.split()
    for i in acct_info:
        acct_info = i.split(',')
        if float(acct_info[1]) < 0:
            print("ERROR! You have a bank account with a negative balance.")
            sys.exit()
        if float(acct_info[1]) < 100:
            f_low.write(acct_info[0])
            f_low.write("\n")
        avg_acct_bal = avg_acct_bal + float(acct_info[1])
        if float(acct_info[1]) > max_account:
            max_account = float(acct_info[1])
        if float(acct_info[1]) > 100:
            value_accts = value_accts + 1
    total_num_accts = total_num_accts + 1

f_low.close()
f.close()
sum_of_accts = avg_acct_bal        
avg_acct_bal = avg_acct_bal / total_num_accts       

print("The total number of accounts is:", total_num_accts)
print("The average account balance is:", avg_acct_bal)       
print("Sum of the account balances is:", sum_of_accts)
print("The maximum account balance is:", max_account)
print("The amount of accounts with a balance over $100 is:", value_accts)
