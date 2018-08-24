#include "node.h"
#include <iostream>

using namespace cs4150;

int main(int argc, char** argv)
{
  {
    node root = node();
    root.add(5);
    root.add(3);
    root.add(4);
    root.add(1);
    root.add(2);
    root.add(8);
    root.add(6);
    root.add(7);
    root.add(10);
    root.add(9);
  }
  
  long long constructor_count = node::get_constructor_count();
  long long destructor_count = node::get_destructor_count();
  
  std::cout << "constructor count: " << constructor_count << std::endl;
  std::cout << "destructor count: " << destructor_count << std::endl;
}
