#include <iostream>
#include <cstdlib>
#include <vector>
#include <string>
#include <unordered_set>
#include <algorithm>

// Typedefs
typedef std::vector<std::string> string_vector;
typedef std::unordered_set<std::string> string_set;

// methods defined below main
int jumble(const string_vector & words);

/***
 * Reads in a list of words from console and prints the number of items that 
 * were not anagrams of another item in the list
 **/
int main()
{
  //read in first line which specifies the number of words n
  int n, k;
  std::cin >> n;
  std::cin >> k;

  // read in each word and place in dictionary
  string_vector dictionary;
  for (int i = 0; i < n; i++)
  {
    std::string word;
    std::cin >> word;
    dictionary.push_back(word);
  }

  // run jumble algorithm and print result
  std::cout << jumble(dictionary) << std::endl;
}

/***
 * Takes a list of words and returns the number of items from the
 * list which is not the anagram of another word in the list
 **/
int jumble(const string_vector & words)
{
  // set up storage
  string_set solutions;
  string_set rejected;

  // for each word in words
  string_vector::const_iterator word = words.begin();
  string_vector::const_iterator end = words.end();

  for (word; word != end; word++)
  {
    //sort the characters in word
    std::string sorted_word = *word;
    std::sort(sorted_word.begin(), sorted_word.end());

    // if we have seen this anagram once before...
    if (solutions.count(sorted_word))
    {
      solutions.erase(sorted_word); // remove from solutions
      rejected.insert(sorted_word); // add it to rejected
    }
    // if we have never seen this anagram before...
    else if (rejected.count(sorted_word) < 1)
    {
      solutions.insert(sorted_word); // add it to solutions
    }
  }

  // return the number of items in solutions
  return solutions.size();
}

