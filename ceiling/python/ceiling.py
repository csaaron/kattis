def main():
    # get first line which containes n and k
    line = input("")
    split_line = line.split(" ")
    n = int(split_line[0])
    k = int(split_line[1])

    storage = []

    # get each sample input (n total)
    for i in range(n):
        line = input("")
        split_line = line.split(" ")

        # make a tree 
        tree = Binary_Tree()
        for number in split_line:
            num = int(number)
            tree.add(num)
        
        #compare tree shape to those in storage, 
        #if no tree of this shape has been found before,
        #put it in storage
        found = False

        for t in storage:
            if tree.compare_shape(t):
                found = True
                break

        if not found:
            storage.append(tree)

    print(len(storage))

class Binary_Tree:
    def __init__(self):
        self.size = 0
        self.root = Node()

    #adds data to this binary search tree
    def add(self, data):
        self.root.add(data)
        self.size = self.size + 1
        return
    
    #compares the shape of this tree to the shape of other, returns false if shapes are identical
    # else returns false
    def compare_shape(self, other):
        #for each tree to be the same shape, they have to have the same size
        if self.size != other.size:
            return False
    
        #get the linearized version of each tree
        self_tree = self.linearized_tree()
        other_tree = other.linearized_tree()

        # check shape of each node in linearized trees, if they aren't equal return false
        for i in range(self.size):
            if self_tree[i].get_shape() != other_tree[i].get_shape():
                return False

        return True

    # If tree is empty, returns None, else returns a list containing the nodes
    # of this tree in linear order
    def linearized_tree(self):
        if self.size == 0:
            return None

        linear_tree = [None] * self.size
        self.explore(self.root, linear_tree)
        return linear_tree

    # Explores the left child, then the right child of the node then adds node to the beginning of arr
    def explore(self, node, arr):
        if node.has_left_child():
            self.explore(node.left_child, arr)
        if node.has_right_child():
            self.explore(node.right_child, arr)

        arr.insert(0, node)
        return

class Node:
    def __init__(self):
        self.left_child = None
        self.right_child = None
        self.data = None

    # returns true of at least one child has data
    def has_child(self):
        return self.left_child is not None or self.right_child is not None

    #returns true if node has a left child
    def has_left_child(self):
        return self.left_child is not None

    # returns true if node has a right child
    def has_right_child(self):
        return self.right_child is not None

    #adds data to node class tree
    def add(self, data):
        # if data is none, do nothing
        if data is None:
            return

        # if stored data is none, can place new data here
        if self.data is None:
            self.data = data
            return
        
        # recursively travel down the left and right children to add the data
        # go left
        elif data < self.data:
            if not self.has_left_child():
                self.left_child = Node()
            self.left_child.add(data)
        # go right
        elif data >= self.data:
            if not self.has_right_child():
                self.right_child = Node()
            self.right_child.add(data)
    
    #returns the shape of this node in integer form. shape = left + right. left = 1 
    #if there is a left child else 0 if there is not, right = 2 if there is a right 
    #child else 0 if there is not (encodes the shape least significant 2 bits 0 to 3)
    def get_shape(self):
        shape = 0
        if self.has_left_child():
            shape += 1
        if self.has_right_child():
            shape += 2
        return shape


if __name__=="__main__":
	main()