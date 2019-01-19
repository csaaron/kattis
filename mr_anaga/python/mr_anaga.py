# Reads in a list of words from console and prints the number of items
# that were not anagrams of another item in the list
def mrAnaga():

    #read in number of words in list
    line = input("")
    split_line = line.split(" ")
    words_num = int(split_line[0])

    dictionary = []

    for i in range(words_num):
        #read in all lines and add them to dictionary
        dictionary.append(input(""))
    
    solutions = jumble(dictionary)

    print(len(solutions))

###
# Takes a list of words and returns a set containing every word from the list
# which is not the anagram of any other word in the list
##
def jumble(words):
    # set up storage
    solutions = set() # a set of unconfirmed anagrams
    rejected = set() # a set of confirmed anagrams

    for word in words:
        # sort the line's characters
        sorted_word = sortWord(word)
        
        # If we have seen this anagram before, remove it from solutions and 
        # place in confirmed
        if sorted_word in solutions:
            solutions.discard(sorted_word)
            rejected.add(sorted_word)
        # if word is not a confirmed anagram add to unconfirmed
        elif sorted_word not in rejected:
            solutions.add(sorted_word)
    
    return solutions

###
# Takes a string and sorts its characters. Returns a string containing the
# sorted chars of word
##
def sortWord(word):
    # sort the letters of the line (returns a list of characters)
    sorted_chars = sorted(word)
    # can use join function to turn sorted list of chars back into a 
    # string
    empty_str = ""
    sorted_word = empty_str.join(sorted_chars)
    return sorted_word

#entry point for program
if __name__ == "__main__":
    mrAnaga()
