/* c++ solution to utah.kattis.com/problems/ceiling written by Aaron Bellis 6/7/2018 */

# ifndef NODE_H
# define NODE_H

# include <cstddef>
# include <vector>

namespace cs4150
{
  /**
   * Node class represents an individual vertex in a binary tree graph.
   */
  class node
  {
    friend class binary_tree;    
    
    private:
      /* pointers to children of this node, if this node has no left or right
       * children, pointers will be NULL */
      node * left_child; 
      node * right_child;
      // the data held by this node
      int data;
      // reports if this node has data
      bool storing_data;
      
      // counters for auditing purposes
      static long long constructor_count;
      static long long destructor_count;
      
    public:
      node();
      
      ~node();

      node(const node & other);
      
      node & operator= (const node & rhs);


      /**
       * Returns true if this node has a right or left child, else returns false
       */
      bool has_child() const;
      /**
       * Returns true if this node has a right child, else returns false
       */
      bool has_right_child() const;
      /**
       * Returns true if this node has a left child, else returns false
       */
      bool has_left_child() const;
      
      /**
       * If this node is not storing data, stores number as its data. If node is storing data
       * adds its data to the tree contained in its left or right child.
       */
      void add(int number);
      
      /**
       * Returns an integer between 0 and 3 inclusive which is the integer shape of this node.
       * shape = left + right. Left = 1 if there is a left child, 0 if there is not.
       * right = 2 if there is a right child, 0 if there is not. (encodes the shape in the 2 least
       * significant bits)
       */
      char get_shape() const;

      /**
       * Returns the number of times a node class constructor has been called. Provided to audit
       * constructors and destructors.
       */
      static long long get_constructor_count();

      /**
       * Returns the number of times a node class destructor has been called. Provided to audit
       * constructors and destructors.
       */
      static long long get_destructor_count();

    private:
      /**
       * Releases all resources used by this object.
       */
      void clean();
      
      /**
       * copies the structure of tree into this node
       */ 
      void explore(const node & tree);

      /**
       * Takes a node and places its shape into shapes in reverse topological order
       */
      static void get_linearized_shapes(const node * graph, std::vector<char> & shapes);
  };
}

# endif
