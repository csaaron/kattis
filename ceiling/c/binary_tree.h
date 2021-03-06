/* c++ solution to utah.kattis.com/problems/ceiling written by Aaron Bellis 6/7/2018 */

# ifndef BINARY_TREE_H
# define BINARY_TREE_H

#include <cstddef>
#include <vector>
#include "node.h"

namespace cs4150
{
  class binary_tree
  {
    private:
      int size;
      node * root;
      
    public:
      /**
       * Creates empty binary_tree instance
       */ 
      binary_tree();
      /**
       * Copy constructor. Copies the contents of other into this binary_tree
       */
      binary_tree(const binary_tree & other);
      /**
       * Destructor for binary_tree class. Ensures all resources used by this object are released
       */
      ~binary_tree();
      
      /**
       * Assignment operator. Assigns contents of rhs into this binary_tree
       */
      binary_tree & operator= (const binary_tree & rhs);
      
      /**
       * adds data to this binary_tree object
       */ 
      void add(int data);
      
      /**
       * Compares the shape of this binary_tree to the shape of other. Returns true if their shapes
       * are the same, else returns false
       */
      bool compare_shape(const binary_tree & other) const;

      /**
       * Compares the shape of this binary_tree to the shape of other. Returns true if their shapes
       * are the same, else returns false
       */
      bool compare_shape_recursive(const binary_tree & other) const;
    private:
      
      /**
       * Compares the shape of node and subtree to the shape of other node and subtree. 
       * Returns true if their shapes are the same, else returns false
       */
      static bool compare_nodes_recursive(const node * this_tree, const node * other_tree);
      
      /**
       * Ensures resources used by this object are released. Essentially destroys this object
       */
      void clean();
      
  };
}

# endif
