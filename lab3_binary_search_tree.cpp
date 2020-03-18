#include <iostream>
#include "lab3_binary_search_tree.hpp"

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
    root = NULL;
    size = 0;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
    for (int i = 0; i < size; ++i) {
        remove( *root);
    }
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
    if (!size) {
        return BinarySearchTree::TaskItem(-1, "N/A");
    } else {
        TaskItem* max = root;
        while (max->right) {
            max = max->right;
        }
        return *max;
    }
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
    if (!size) {
        return BinarySearchTree::TaskItem(-1, "N/A");
    } else {
        TaskItem* min= root;
        while (min->left) {
            min = min->left;
        }
        return *min;
    }
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
    return recursive_height(root);
}

//Purpose: recursive algorithm for tree height
unsigned int BinarySearchTree::recursive_height(BinarySearchTree::TaskItem* val) const {
    if (val == NULL)
        return -1;
    else
        return 1 + (recursive_height(val->left) >= recursive_height(val->right) ? recursive_height(val->left) : recursive_height(val->right));
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const { //Inorder Traversal
    print(root);
}

//Purpose: Print contents of tree in-order recursively
void BinarySearchTree::print(BinarySearchTree::TaskItem* val) const {
    if (val == NULL)
        return;
    print(val->left);
    cout << "Priority: " << val->priority << "\t" << "Description: " << val->description << endl;
    print(val->right);
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
    if (size != 0 && val.priority)
        return exists(val, *root);
    else
        return false;
}

//Overloaded function to traverse tree using recursion and check for existence
bool BinarySearchTree::exists(BinarySearchTree::TaskItem val, BinarySearchTree::TaskItem cur) const {
    if (!val.priority)
        return false;
    if (val.priority == cur.priority && val.description == cur.description)
        return true;
    else if (val.priority < cur.priority)
        return exists(val, *cur.left);
    else if (val.priority > cur.priority)
        return exists(val, *cur.right);
    else
        return false;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return root;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return &root;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	return 0;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
    if (size == 0)
        root = new TaskItem(val.priority, val.description);
    else if (exists(val))
        return false;
    else
        insert(val, root);
    size++;
    return true;
}

//Recursively goes through tree to insert new node if the input is valid
void BinarySearchTree::insert(BinarySearchTree::TaskItem val, BinarySearchTree::TaskItem *cur) {
    if (val.priority < cur->priority && !cur->left)
        cur->left = new TaskItem(val.priority, val.description);
    else if (val.priority > cur->priority && !cur->right)
        cur->right = new TaskItem(val.priority, val.description);
    else if (val.priority < cur->priority)
        insert(val, cur->left);
    else if (val.priority > cur->priority)
        insert(val, cur->right);
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val) {
    if (!exists(val))
        return false;
    else
        remove(val, root);
    size--;
    return true;
}

//Recursively goes through tree to remove the input node
void BinarySearchTree::remove(BinarySearchTree::TaskItem val, BinarySearchTree::TaskItem *cur) {

    if (val.priority == cur->priority && root == cur) {
        TaskItem* temp = cur;
        if (!temp->left && ! temp->right) {
            delete temp;
            temp = NULL;
        } else if(temp->left && temp->right) {
            TaskItem* min = temp->right;
            while (min->left) {
                min = min->left;
            }
            root = min;
            min->left = temp->left;
            delete temp;
            temp = NULL;
        } else if (temp->left || temp->right) {
            root = temp->left ? temp->left : temp->right;
            delete temp;
            temp = NULL;
        }
    }
    else if (val.priority == cur->left->priority) {
        TaskItem* temp = cur->left;
        if (!temp->left && ! temp->right) {
            delete temp;
            temp = NULL;
        } else if(temp->left && temp->right) {
            TaskItem* min = temp->right;
            while (min->left) {
                min = min->left;
            }
            cur->left = min;
            min->left = temp->left;
            delete temp;
            temp = NULL;
        } else if (temp->left || temp->right) {
         cur->left = temp->left ? temp->left : temp->right;
         delete temp;
         temp = NULL;
        }
    }
    else if (val.priority == cur->right->priority) {
        TaskItem* temp = cur->right;
        if (!temp->left && ! temp->right) {
            delete temp;
            temp = NULL;
        } else if(temp->left && temp->right) {
            TaskItem* min = temp->right;
            while (min->left) {
                min = min->left;
            }
            cur->right = min;
            min->left = temp->left;
            delete temp;
            temp = NULL;
        } else if (temp->left || temp->right) {
            cur->right = temp->left ? temp->left : temp->right;
            delete temp;
            temp = NULL;
        }
    }
    else if (val.priority < cur->priority) {
        remove(val, cur->left);
    }
    else if (val.priority > cur->priority) {
        remove(val, cur->right);
    }
}



