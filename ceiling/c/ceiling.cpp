/* c++ solution to utah.kattis.com/problems/ceiling written by Aaron Bellis 6/7/2018 */

#include "node.h"
#include "binary_tree.h"
#include <iostream>
#include <vector>

using namespace cs4150;

int main(int argc, char** argv)
{
  int n, k;
  std::cin >> n; // number of ceiling prototypes
  std::cin >> k; // number of layers in each prototype
  
  std::vector<binary_tree*> trees; //storage for unique types
  trees.reserve(n); //reserve enough space to avoid resize
  
  // read each line
  for (int i = 0; i < n; i++)
  {
    binary_tree * tree = new binary_tree();
    // read each layer
    for (int j = 0; j < k; j++)
    {
      int layer;
      std::cin >> layer;
      tree->add(layer);
    }
    
    // compare this tree to each unique tree in trees
    std::vector<binary_tree*>::iterator it = trees.begin();
    std::vector<binary_tree*>::iterator end = trees.end();
    
    bool matches_shape = false;
    for (it; it != end; it++)
    {
      if (tree->compare_shape(**it))
      {
        matches_shape = true;
        break;
      }
    }
    
    // if a match for the shape wasn't found, put it in the vector
    if (!matches_shape)
    {
      trees.push_back(tree);
    }
    else
    {
      delete tree;
      tree = NULL;
    }
  }
  
  // print the number of unique shaped prototypes
  std::cout << trees.size() << std::endl;
}
