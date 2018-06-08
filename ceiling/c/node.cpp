/* c++ solution to utah.kattis.com/problems/ceiling written by Aaron Bellis 6/7/2018 */

# include "node.h"

// initialize private static members
long long cs4150::node::constructor_count = 0;
long long cs4150::node::destructor_count = 0;

cs4150::node::node()
{
  left_child = NULL;
  right_child = NULL;
  data = 0;
  storing_data = false;
  
  constructor_count++;
}

cs4150::node::node(const cs4150::node & other)
{
  // ensure well formed class
  left_child = NULL;
  right_child = NULL;
  data = 0;
  storing_data = false;
  
  // let the assignment operator do the work
  *this = other;
  
  constructor_count++;
}

cs4150::node::~node()
{
  clean();
  
  destructor_count++;
}

cs4150::node & cs4150::node::operator= (const cs4150::node & rhs)
{ 
  // release resources used by this object
  clean();
  
  explore(rhs); 
  
  // always return *this for assignment operator
  return *this;
}

/**
 * Returns true if this node has a right or left child, else returns false
 */
bool cs4150::node::has_child() const
{
  return left_child != NULL || right_child != NULL;
}

/**
 * Returns true if this node has a right child, else returns false
 */
bool cs4150::node::has_right_child() const
{
  return right_child != NULL;
}

/**
 * Returns true if this node has a left child, else returns false
 */
bool cs4150::node::has_left_child() const
{
  return left_child != NULL;
}

/**
 * If this node is not storing data, stores number as its data. If node is storing data
 * adds its data to the tree contained in its left or right child.
 */
void cs4150::node::add(int number)
{
  // base case for recursive method, if this node is not storing data, store nubmer
  // here
  if (!storing_data)
  {
    data = number;
    storing_data = true;
    return;
  }
  
  // if number is less than data, add it to left tree
  if (number < data)
  {
    // if left tree hasn't been created yet, make it
    if (!has_left_child())
    {
      left_child = new node();
    }
    
    // add to left tree
    left_child->add(number);
  }
  // if number is greater than or equal to data, add it to right tree
  else if (number >= data)
  {
    // if right child has yet to be created, make it
    if (!has_right_child())
    {
      right_child = new node();
    }
    
    // add to right tree
    right_child->add(number);
  }
  
}

/**
 * Returns an integer between 0 and 3 inclusive which is the integer shape of this node.
 * shape = left + right. Left = 1 if there is a left child, 0 if there is not.
 * right = 2 if there is a right child, 0 if there is not. (encodes the shape in the 2 least
 * significant bits)
 */
char cs4150::node::get_shape() const
{
  char shape = 0;
  if (has_left_child())
  {
    shape += 1;
  }
  if (has_right_child())
  {
    shape += 2;
  }
  return shape;
}

/**
 * Returns the number of times a node class constructor has been called. Provided to audit
 * constructors and destructors.
 */
long long cs4150::node::get_constructor_count()
{
  return constructor_count;
}

/**
 * Returns the number of times a node class destructor has been called. Provided to audit
 * constructors and destructors.
 */
long long cs4150::node::get_destructor_count()
{
  return destructor_count;
}

/**
 * Releases all resources used by this object.
 */
void cs4150::node::clean()
{
  if (has_left_child())
  {
    delete left_child;
    left_child = NULL;
  }
  if (has_right_child())
  {
    delete right_child;
    right_child = NULL;
  }
  
  data = 0;
  storing_data = false;
  
}

/**
 * copies the contents of tree into this node
 */ 
void cs4150::node::explore(const cs4150::node & tree)
{
  add(tree.data);
  
  if (tree.has_left_child())
  {
    explore(*(tree.left_child)); 
  }
  if (tree.has_right_child())
  {
    explore(*(tree.right_child));
  }
}
