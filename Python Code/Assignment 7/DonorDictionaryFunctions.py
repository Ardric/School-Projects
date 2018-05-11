#Daniel Lowdermilk
#Worked with Nick Keithley

# ###########################
# the donors dictionary has the name of the person as the key
# and the amount donated as the value.
# This function returns the total amount donated by all people.
def totalDonations(donordict):
    total_donated = 0
    for key, value in donordict.items():
        total_donated = total_donated + value
    return total_donated



# ###########################
# the donors dictionary has the name of the person as the key
# and the amount donated as the value.
# This function returns the total amount donated by all people
# whose name begins with the letter "T".
def totalDonationsBySome(donordict):
    total_donated_by_T = 0
    for key, value in donordict.items():
        if key[0] == 'T':
            total_donated_by_T = total_donated_by_T + value
    return total_donated_by_T






# ###########################
# the donors dictionary has the name of the person as the key
# and the amount donated as the value.
# This function returns a list of the names of all donors who
# donated at least $50
def bigDonors(donordict):
    donated_fifty = []
    for key, value in donordict.items():
        if value >= 50:
            donated_fifty.append(key)
    return donated_fifty


# ###########################
# the donors dictionary has the name of the person as the key
# and the amount donated as the value.
# This function returns the name of the person who donated the most
# money.
# A tie?  Pick one.
def largestDonor(donordict):
    largest_donor = ""
    largest_donation = 0
    for key, value in donordict.items():
        if value > largest_donation:
            largest_donation = value
            largest_donor = key
    return largest_donor




# ###########################
# the donors dictionary has the name of the person as the key
# and the amount donated as the value.
# This function returns the name of the person who donated the most
# money.
# A tie?  return a list of the names of the people who are tied.
def largestDonor2(donordict):
    largest_donor_list = []
    largest_donor = ""
    largest_donation = 0
    for key, value in donordict.items():
        if value > largest_donation:
            largest_donation = value
            largest_donor = key
    largest_donor_list.append(largest_donor)

    for key, value in donordict.items():
        if value == largest_donation and key not in largest_donor_list:
            largest_donor_list.append(key)
            
    return largest_donor_list


# ###########################
# the donors dictionary has the name of the person as the key
# and the amount donated as the value.
# This function takes care of the fact that the indicated person donated
# money.
# If the person is already in the dictionary, the amount is added to the
# old amount.  If not, the  person and the new donation are added to the
# dictionary.
def processNewDonation(donordict, donorName, donationAmount):
    return 0




###############################################################
donors = {}
donors["Joe"] = 10
donors["Terry"] = 15
donors["Tom"] = 50
donors["Chris"] = 40
donors["Tina"] = 45
donors["Jerry"] = 75
donors["Skyler"] = 75
donors["Timothy"] = 60
