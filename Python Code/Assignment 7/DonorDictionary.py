#Daniel Lowdermilk

from DonorDictionaryFunctions import *
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



print(donors)
print("total donations: $" , totalDonations(donors))

print("total donations, names beginning with T: $", totalDonationsBySome(donors))

print ("Big donors: " , bigDonors(donors))

print("Biggest donor: " , largestDonor(donors))

print("Biggest donor (version 2): " , largestDonor2(donors))


print("----------")
processNewDonation(donors,"Anne",40)
processNewDonation(donors,"Joe",15)
processNewDonation(donors,"Sarah",20)
processNewDonation(donors,"Tina",25)
processNewDonation(donors,"Timothy",45)
processNewDonation(donors,"Avery",15)


print("some donations came in:")
print(donors)
print("total donations: $" , totalDonations(donors))

print("total donations, names beginning with T: $", totalDonationsBySome(donors))

print ("Big donors: " , bigDonors(donors))

print("Biggest donor: " , largestDonor(donors))

print("Biggest donor (version 2): " , largestDonor2(donors))
