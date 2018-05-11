#Daniel Lowdermilk

#Tester

from DictionaryFileFunctions import *

words = getWordList("Dictionary.py")
print(words)

interestingWords = getInterestingWords(words)
print(interestingWords)

reallyinterestingwords = getReallyInterestingWords(words)
print(reallyinterestingwords)

pairs_of_interest = displayPairsOfInterest(interestingWords, reallyinterestingwords)

writePairsOfInterest("Test.py", pairs_of_interest)
