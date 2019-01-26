ceiling: node.h node.cpp binary_tree.h binary_tree.cpp ceiling.cpp node.o binary_tree.o
	g++ -o ceiling node.o binary_tree.o ceiling.cpp

node.o: node.h node.cpp
	g++ -c node.cpp

binary_tree.o: binary_tree.h binary_tree.cpp
	g++ -c binary_tree.cpp

clean:
	rm -f ceiling node.o binary_tree.o