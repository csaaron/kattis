/* c++ solution to utah.kattis.com/problems/ceiling written by Aaron Bellis 6/7/2018 */

#include "binary_tree.h"

/**
 * Creates empty binary_tree instance
 */ 
cs4150::binary_tree::binary_tree()
{
  size = 0;
  root = new node();
}

/**
 * Copy constructor. Copies the contents of other into this binary_tree
 */
cs4150::binary_tree::binary_tree(const binary_tree & other)
{
  size = 0;
  root = new node();
  
  *this = other;
}

/**
 * Destructor for binary_tree class. Ensures all resources used by this object are released
 */
cs4150::binary_tree::~binary_tree()
{
  clean();
}

/**
 * Assignment operator. Assigns contents of rhs into this binary_tree
 */
cs4150::binary_tree & cs4150::binary_tree::operator= (const binary_tree & rhs)
{
  clean();
  
  root = new node(*(rhs.root));
  size = rhs.size;
  
  // always do this for assignment operator
  return *this;
}

/**
 * adds data to this binary_tree object
 */ 
void cs4150::binary_tree::add(int data)
{
  root->add(data);
  size++;
}

/**
 * Compares the shape of this binary_tree to the shape of other. Returns true if their shapes
 * are the same, else returns false
 */
bool cs4150::binary_tree::compare_shape(const cs4150::binary_tree & other) const
{
  // if sizes of both trees are not the same, cannot have the same shape
  if (size != other.size)
  {
    return false;
  }
  
  // create a vector for this tree's shapes and make sure it has enough space to avoid resize
  std::vector<char> this_linearized_tree;
  this_linearized_tree.reserve(size);
  // place shapes in vector, will be in reverse topological order
  node::get_linearized_shapes(root, this_linearized_tree);
  
  // create a vector for other tree's shapes and make sure it has enough space to avoid resize
  std::vector<char> other_linearized_tree;
  other_linearized_tree.reserve(other.size);
  // place shapes in vector, will be in reverse topological order
  node::get_linearized_shapes(other.root, other_linearized_tree);
  
  // get a reverse iterator to for this tree
  std::vector<char>::reverse_iterator this_it = this_linearized_tree.rbegin();
  std::vector<char>::reverse_iterator this_end = this_linearized_tree.rend();
  
  // get a reverse iterator for other tree
  std::vector<char>::reverse_iterator other_it = other_linearized_tree.rbegin();
  std::vector<char>::reverse_iterator other_end = other_linearized_tree.rend();
  
  // compare each element of vectors in reverse order
  for (; this_it != this_end && other_it != other_end ; this_it++, other_it++)  
  {
    // if element shape is not same, trees are not same shape
    if (*this_it != *other_it)
    {
      return false;
    }
  }
  
  return true;
  
}

/**
 * Compares the shape of this binary_tree to the shape of other. Returns true if their shapes
 * are the same, else returns false
 */
bool cs4150::binary_tree::compare_shape_recursive(const cs4150::binary_tree & other) const
{
  if (this->size != other.size)
  {
    return false;
  }

  cs4150::node * lhs_node = root;
  cs4150::node * rhs_node = other.root;

  return cs4150::binary_tree::compare_nodes_recursive(lhs_node, rhs_node);
}

/**
 * Compares the shape of node and subtree to the shape of other node and subtree.
 * Returns true if their shapes are the same, else returns false
 */
bool cs4150::binary_tree::compare_nodes_recursive(const cs4150::node * this_tree, const cs4150::node * other_tree)
{
  // base case for recursion. If both are null shape is the same
  if (!this_tree && !other_tree)
  {
    return true;
  }
  // if only one is null shape is different
  else if (!this_tree || !other_tree)
  {
    return false;
  }
  
  // if this shape is not the same as the other, return false
  if (this_tree->get_shape() != other_tree->get_shape())
  {
    return false;
  }
  // if shapes are same, continue down the left path on both sub trees, 
  // then follow down the right tree.
  else
  {
    return compare_nodes_recursive(&(this_tree->get_left_child()), &(other_tree->get_left_child())) &&
      compare_nodes_recursive(&(this_tree->get_right_child()), &(other_tree->get_right_child()));
  }

}

/**
 * Ensures resources used by this object are released. Essentially destroys this object
 */
void cs4150::binary_tree::clean()
{
  delete root;
  root = NULL;
  size = 0;
}
