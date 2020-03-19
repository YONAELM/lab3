#ifndef LAB3_TESTS_HPP
#define LAB3_TESTS_HPP

#define ASSERT_TRUE(T) if (!(T)) return false;
#define ASSERT_FALSE(T) if ((T)) return false;

#include <algorithm>
#include <sstream>
#include <queue>
#include <array>

#include "lab3_priority_queue.hpp"
#include "lab3_binary_search_tree.hpp"

class PriorityQueueTest {
public:
    // PURPOSE: Tests if the new queue is valid
    bool test1() {
        // Case 1: create a queue of more than one element
        PriorityQueue q(5);
        ASSERT_TRUE( q.empty() );
        ASSERT_TRUE( !q.full() );
        ASSERT_TRUE( q.get_size() == 0 );

        // Case 2: create a queue of no elements
        PriorityQueue q2(0);
        ASSERT_TRUE( q2.empty() );
        ASSERT_TRUE( q2.get_size() == 0 );
        ASSERT_TRUE( q2.full() );

        // Case 3: create a queue of one elements
        PriorityQueue q3(1);
        ASSERT_TRUE( q3.empty() );
        ASSERT_TRUE( q3.get_size() == 0 );
        ASSERT_FALSE( q3.full() );
        return true;
    }

    // PURPOSE: Tests enqueue of one item and then dequeue of that item
    bool test2() {
        //Case 1: enqueue one item and dequeue one item
        PriorityQueue q(8);
        PriorityQueue::TaskItem t(1, "Cook dinner");
        ASSERT_TRUE(q.enqueue(t));
        ASSERT_FALSE( q.empty() );
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE( q.empty() );

        //Case 2: enqueue multiple items and remove multiple items
        PriorityQueue::TaskItem t1(1, "Cook dinner");
        q.enqueue(t1);
        PriorityQueue::TaskItem t2(2, "Eat food");
        q.enqueue(t2);
        PriorityQueue::TaskItem t3(3, "Wash dishes");
        q.enqueue(t3);
        PriorityQueue::TaskItem t4(4, "Dry dishes");
        q.enqueue(t4);
        PriorityQueue::TaskItem t5(5, "Take out garbage");
        q.enqueue(t5);
        PriorityQueue::TaskItem t6(6, "Take out recycling");
        q.enqueue(t6);
        PriorityQueue::TaskItem t7(7, "Wash counter");
        q.enqueue(t7);
        PriorityQueue::TaskItem t8(8, "Wash hands");
        q.enqueue(t8);
        q.dequeue();
        q.dequeue();
        q.dequeue();
        q.dequeue();
        q.dequeue();
        q.dequeue();
        q.dequeue();
        q.dequeue();
        ASSERT_TRUE( q.empty() );

        //Case 3: enqueue duplicate values
        ASSERT_TRUE(q.enqueue(t1));
        ASSERT_FALSE(q.enqueue(t1));
        ASSERT_TRUE(q.get_size() == 1);

        return true;
    }

    // PURPOSE: Tests enqueue too many
    bool test3() {
        PriorityQueue q(8);
        PriorityQueue::TaskItem t1(1, "Cook dinner");
        q.enqueue(t1);
        PriorityQueue::TaskItem t2(2, "Eat food");
        q.enqueue(t2);
        PriorityQueue::TaskItem t3(3, "Wash dishes");
        q.enqueue(t3);
        PriorityQueue::TaskItem t4(4, "Dry dishes");
        q.enqueue(t4);
        PriorityQueue::TaskItem t5(5, "Take out garbage");
        q.enqueue(t5);
        PriorityQueue::TaskItem t6(6, "Take out recycling");
        q.enqueue(t6);
        PriorityQueue::TaskItem t7(7, "Wash counter");
        q.enqueue(t7);
        PriorityQueue::TaskItem t8(8, "Wash hands");
        q.enqueue(t8);
        PriorityQueue::TaskItem t9(9, "Wash hands");
        ASSERT_FALSE(q.enqueue(t9));
        q.dequeue();
        ASSERT_TRUE(q.enqueue(t9));
        return true;
    }

    // PURPOSE: Tests enqueue too many then dequeue too many
    bool test4() {
        //Case 1: enqueue to capacity, try to enqueue at capacity
        PriorityQueue q(8);
        PriorityQueue::TaskItem t1(1, "Cook dinner");
        q.enqueue(t1);
        PriorityQueue::TaskItem t2(2, "Eat food");
        q.enqueue(t2);
        PriorityQueue::TaskItem t3(3, "Wash dishes");
        q.enqueue(t3);
        PriorityQueue::TaskItem t4(4, "Dry dishes");
        q.enqueue(t4);
        PriorityQueue::TaskItem t5(5, "Take out garbage");
        q.enqueue(t5);
        PriorityQueue::TaskItem t6(6, "Take out recycling");
        q.enqueue(t6);
        PriorityQueue::TaskItem t7(7, "Wash counter");
        q.enqueue(t7);
        PriorityQueue::TaskItem t8(8, "Wash hands");
        q.enqueue(t8);
        PriorityQueue::TaskItem t9(9, "Dry hands");
        ASSERT_FALSE(q.enqueue(t9))

        //Case 2: dequeue to nothing, try to dequeue from empty
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.dequeue());
        ASSERT_TRUE(q.dequeue());
        ASSERT_FALSE(q.dequeue());

        //Case 3: enqueue out of order
        q.enqueue(t8);
        q.enqueue(t5);
        q.enqueue(t4);
        q.enqueue(t2);
        q.enqueue(t6);
        q.enqueue(t1);
        q.enqueue(t7);
        q.enqueue(t3);
        // verify with visual inspection
        ASSERT_TRUE(q.max().priority == 8);

        //Case 4: non contingous priority
        PriorityQueue q1(8);
        PriorityQueue::TaskItem tk1(9000, "Cook dinner");
        q1.enqueue(tk1);
        PriorityQueue::TaskItem tk2(101, "Eat food");
        q1.enqueue(tk2);
        PriorityQueue::TaskItem tk3(3, "Wash dishes");
        q1.enqueue(tk3);
        PriorityQueue::TaskItem tk4(1, "Dry dishes");
        q1.enqueue(tk4);
        PriorityQueue::TaskItem tk5(50, "Take out garbage");
        q1.enqueue(tk5);
        PriorityQueue::TaskItem tk6(4242, "Take out garbage");
        q1.enqueue(tk6);
        PriorityQueue::TaskItem tk7(1812, "Take out garbage");
        q1.enqueue(tk7);
        PriorityQueue::TaskItem tk8(2000, "Take out garbage");
        q1.enqueue(tk8);
        PriorityQueue::TaskItem tk9(2001, "Take out garbage");
        ASSERT_FALSE(q1.enqueue(tk9));
        ASSERT_TRUE(q1.max().priority == 9000);
        q1.dequeue();
        ASSERT_TRUE(q1.max().priority == 4242);
        q1.dequeue();
        ASSERT_TRUE(q1.max().priority == 2000);
        q1.dequeue();
        ASSERT_TRUE(q1.max().priority == 1812);
        q1.dequeue();
        ASSERT_TRUE(q1.max().priority == 101);
        q1.dequeue();
        ASSERT_TRUE(q1.max().priority == 50);
        q1.dequeue();
        ASSERT_TRUE(q1.max().priority == 3);
        q1.dequeue();
        ASSERT_TRUE(q1.max().priority == 1);
        q1.dequeue();
        ASSERT_TRUE(q1.empty());

        //Case 5: enqueue into a 0 capacity
        PriorityQueue q2(0);
        ASSERT_FALSE(q2.enqueue(t1));

        //Case 6: dequeue from 0 capacity
        ASSERT_FALSE(q2.dequeue());
        return true;
    }
};

class BinarySearchTreeTest {
public:
	bool insert_nodes(BinarySearchTree &tree, int *in, int nin) {
		for(int i = 0; i < nin; i++) {
			ASSERT_TRUE(tree.insert(BinarySearchTree::TaskItem(in[i],"Test Task")));
		}
		return true;
	}

	// PURPOSE: Traverse the tree using breadth-first traversal
	// Output is as follows: "val1 val2 ... valN"
	std::string level_order(BinarySearchTree::TaskItem* root) {
		if (!root) {
      		return "";
    	}    

		std::stringstream ss;
		std::queue<BinarySearchTree::TaskItem*> node_queue;
		node_queue.push(root);
		while (!node_queue.empty()) {
			BinarySearchTree::TaskItem* cur_node = node_queue.front();
			node_queue.pop();
			ss << cur_node->priority << " ";
			if (cur_node->left) {
				node_queue.push(cur_node->left);
			}
			if (cur_node->right) {
				node_queue.push(cur_node->right);
			}
		}
    
		std::string level_order_str = ss.str();

		return level_order_str.substr(0, level_order_str.size() - 1);
	}

	// PURPOSE: Tests if the new tree is valid
	bool test1() {
		std::string expected_tree_level_order = "";
    
		BinarySearchTree bst;
		ASSERT_TRUE(bst.root == NULL);
		ASSERT_TRUE(bst.size == 0 && bst.get_size() == 0);
    
		// compare the tree's representation to the expected tree
		std::string tree_level_order = level_order(bst.root);
		ASSERT_TRUE(tree_level_order.compare(expected_tree_level_order) == 0)
		return true;
	}

	// PURPOSE: Tests a tree with one node
	bool test2() {
	    BinarySearchTree Test2;
	    ASSERT_TRUE(Test2.get_size() == 0);
        BinarySearchTree::TaskItem t(1, "Cook dinner");
        BinarySearchTree::TaskItem t2(2, "Eat food");

        ASSERT_TRUE(Test2.insert(t));
	    ASSERT_TRUE(Test2.get_size() == 1);
	    ASSERT_TRUE(Test2.exists(t));
	    ASSERT_FALSE(Test2.exists(t2));
	    ASSERT_TRUE(Test2.max() == t);
	    ASSERT_TRUE(Test2.min() == t);
	    ASSERT_TRUE(Test2.height() == 0);
	    ASSERT_FALSE(Test2.insert(t));
	    ASSERT_TRUE(Test2.remove(t));
	    ASSERT_FALSE(Test2.remove(t2));
        ASSERT_TRUE(Test2.get_size() == 0);

		return true;
	}

	// PURPOSE: Tests insert, remove, and size on linear list formation with three elements
	bool test3() {
        BinarySearchTree Test3;
	    int linear[3] = {42,55,12};

        for (int i = 0; i < 3 ; ++i) {
        ASSERT_TRUE(Test3.insert(BinarySearchTree::TaskItem(linear[i], "Element")));
        }
        ASSERT_TRUE(Test3.get_size() == 3);

        for (int j = 0; j < 3; ++j) {
            ASSERT_TRUE(Test3.exists(BinarySearchTree::TaskItem(linear[j],"Element")));
        }
        while (Test3.get_size())
            Test3.remove(Test3.min());

        ASSERT_TRUE(Test3.get_size() == 0);
		return true;
	}

	// PURPOSE: Tests removal of a node with one child
	bool test4() {
		BinarySearchTree Test4;
        BinarySearchTree::TaskItem t1(1, "Cook dinner");
        BinarySearchTree::TaskItem t2(2, "Eat food");
        BinarySearchTree::TaskItem t3(3, "Wash dishes");
        BinarySearchTree::TaskItem t4(4, "Dry dishes");

        ASSERT_TRUE(Test4.insert(t3));
        ASSERT_TRUE(Test4.insert(t2));
        ASSERT_TRUE(Test4.get_size() == 2);
        ASSERT_TRUE(Test4.exists(t3));
        ASSERT_TRUE(Test4.remove(t3));
        ASSERT_FALSE(Test4.exists(t3));
        ASSERT_TRUE(Test4.max() == t2);
        ASSERT_TRUE(Test4.get_size() == 1);
        ASSERT_TRUE(Test4.insert(t3));
        ASSERT_TRUE(Test4.min() == t2);
        ASSERT_TRUE(Test4.insert(t1));
        ASSERT_TRUE(Test4.min() == t1);
        ASSERT_TRUE(Test4.insert(t4));
        ASSERT_TRUE(Test4.get_size() == 4);
        ASSERT_TRUE(Test4.remove(t3));
        ASSERT_TRUE(Test4.max() == t4);
        ASSERT_FALSE(Test4.exists(t3));
        ASSERT_TRUE(Test4.min() == t1);

        return true;
    }

	// PURPOSE: Tests insert of multiple elements and remove till nothing remains
	bool test5() {
        BinarySearchTree Test5;
        BinarySearchTree::TaskItem t1(1, "Cook dinner");
        BinarySearchTree::TaskItem t2(2, "Eat food");
        BinarySearchTree::TaskItem t3(3, "Wash dishes");
        BinarySearchTree::TaskItem t4(4, "Dry dishes");
        BinarySearchTree::TaskItem t5(5, "Take out garbage");
        BinarySearchTree::TaskItem t6(6, "Take out recycling");
        BinarySearchTree::TaskItem t7(7, "Wash counter");
        BinarySearchTree::TaskItem t8(8, "Wash hands");

        ASSERT_TRUE(Test5.insert(t1));
        ASSERT_TRUE(Test5.get_size() == 1);
        ASSERT_TRUE(Test5.insert(t2));
        ASSERT_TRUE(Test5.get_size() == 2);
        ASSERT_TRUE(Test5.insert(t3));
        ASSERT_TRUE(Test5.get_size() == 3);
        ASSERT_TRUE(Test5.insert(t4));
        ASSERT_TRUE(Test5.get_size() == 4);
        ASSERT_TRUE(Test5.insert(t5));
        ASSERT_TRUE(Test5.get_size() == 5);
        ASSERT_TRUE(Test5.insert(t6));
        ASSERT_TRUE(Test5.get_size() == 6);
        ASSERT_TRUE(Test5.insert(t7));
        ASSERT_TRUE(Test5.get_size() == 7);
        ASSERT_TRUE(Test5.insert(t8));
        ASSERT_TRUE(Test5.get_size() == 8);


        while(Test5.get_size() != 0) {
            ASSERT_TRUE(Test5.remove(Test5.max()));
        }
        ASSERT_TRUE(Test5.get_size() == 0);

        return true;
	}
 
	// PURPOSE: Tests removal of root node when both children of root have two children
	bool test6() {
	    BinarySearchTree Test6;
        BinarySearchTree::TaskItem t1(1, "Cook dinner");
        BinarySearchTree::TaskItem t2(2, "Eat food");
        BinarySearchTree::TaskItem t3(3, "Wash dishes");
        BinarySearchTree::TaskItem t4(4, "Dry dishes");
        BinarySearchTree::TaskItem t5(5, "Take out garbage");
        BinarySearchTree::TaskItem t6(6, "Take out recycling");
        BinarySearchTree::TaskItem t7(7, "Wash counter");
        BinarySearchTree::TaskItem t8(8, "Wash hands");

        ASSERT_TRUE(Test6.insert(t4));
        ASSERT_TRUE(Test6.insert(t2));
        ASSERT_TRUE(Test6.insert(t1));
        ASSERT_TRUE(Test6.insert(t3));
        ASSERT_TRUE(Test6.insert(t6));
        ASSERT_TRUE(Test6.insert(t5));
        ASSERT_TRUE(Test6.insert(t7));

        // Tree is in the form where both children of root have two children
        ASSERT_TRUE(Test6.get_size() == 7);
        ASSERT_TRUE(Test6.remove(t4));
        ASSERT_TRUE(Test6.get_size() == 6);
        ASSERT_TRUE(Test6.remove(t5));

        return true;
	}

	// PURPOSE: Tests depth with many inserts and some removes
	bool test7() {BinarySearchTree bst;
        ASSERT_TRUE(bst.height() == 0);
        BinarySearchTree::TaskItem t1(101, "Cook dinner");
        ASSERT_TRUE(bst.insert(t1));
        ASSERT_TRUE(bst.height() == 0);
        BinarySearchTree::TaskItem t2(2, "Eat food");
        ASSERT_TRUE(bst.insert(t2));
		ASSERT_TRUE(bst.height() == 1);
        BinarySearchTree::TaskItem t3(1, "Wash dishes");
        ASSERT_TRUE(bst.insert(t3));
		ASSERT_TRUE(bst.height() == 2);
        //test inserting duplicates not allowed
        ASSERT_FALSE(bst.insert(t3));
        ASSERT_TRUE(bst.height() == 2);
        BinarySearchTree::TaskItem t4(1001, "Dry dishes");
        bst.insert(t4);
        ASSERT_TRUE(bst.height() == 2);
        BinarySearchTree::TaskItem t5(10001, "Take out garbage");
        bst.insert(t5);
        ASSERT_TRUE(bst.height() == 2);
        //test remove of last inserted value
        ASSERT_TRUE(bst.remove(t5));
        ASSERT_TRUE(bst.height() == 2);
        //test remove of middle value
        ASSERT_TRUE(bst.exists(t3));
        ASSERT_TRUE(bst.remove(t3));
        ASSERT_TRUE(bst.height() == 1);
        //test remove of first value
        ASSERT_TRUE(bst.exists(t1));
        ASSERT_TRUE(bst.remove(t1));
        ASSERT_TRUE(bst.height() == 1);
        BinarySearchTree::TaskItem t6(93, "Take out recycling");
        bst.insert(t6);
        ASSERT_TRUE(bst.height() == 2);
        BinarySearchTree::TaskItem t7(7000, "Wash counter");
        bst.insert(t7);
        ASSERT_TRUE(bst.height() == 2);
        BinarySearchTree::TaskItem t8(8, "Wash hands");
        bst.insert(t8);
        ASSERT_TRUE(bst.height() == 3);
        //test remove to empty
        ASSERT_TRUE(bst.remove(t8));
        ASSERT_TRUE(bst.height() == 2);
        ASSERT_TRUE(bst.remove(t7));
        ASSERT_TRUE(bst.height() == 2);
        ASSERT_TRUE(bst.remove(t6));
        ASSERT_TRUE(bst.height() == 1);
        ASSERT_TRUE(bst.remove(t4));
        ASSERT_TRUE(bst.height() == 0);
        ASSERT_TRUE(bst.remove(t2));
        ASSERT_TRUE(bst.height() == 0);
        return true;
	}

// PURPOSE: Tests lots of inserts and removes
    bool test8() {
        BinarySearchTree bst;
        BinarySearchTree::TaskItem empt(-1, "N/A");
        ASSERT_TRUE(bst.max() == empt);
        ASSERT_TRUE(bst.min() == empt);
        BinarySearchTree::TaskItem t1(101, "Cook dinner");
        ASSERT_TRUE(bst.insert(t1));
        ASSERT_TRUE(bst.exists(t1));
        ASSERT_TRUE(bst.get_size() == 1);
        ASSERT_TRUE(bst.max() == t1);
        ASSERT_TRUE(bst.min() == t1);
        BinarySearchTree::TaskItem t2(2, "Eat food");
        ASSERT_TRUE(bst.insert(t2));
        ASSERT_TRUE(bst.exists(t2));
        ASSERT_TRUE(bst.get_size() == 2);
        ASSERT_TRUE(bst.max() == t1);
        ASSERT_TRUE(bst.min() == t2);
        BinarySearchTree::TaskItem t3(1, "Wash dishes");
        ASSERT_TRUE(bst.insert(t3));
        ASSERT_TRUE(bst.exists(t3));
        ASSERT_TRUE(bst.get_size() == 3);
        ASSERT_TRUE(bst.max() == t1);
        ASSERT_TRUE(bst.min() == t3);
        //test inserting duplicates not allowed
        ASSERT_FALSE(bst.insert(t3));
        BinarySearchTree::TaskItem t4(1001, "Dry dishes");
        bst.insert(t4);
        ASSERT_TRUE(bst.exists(t4));
        ASSERT_TRUE(bst.get_size() == 4);
        ASSERT_TRUE(bst.max() == t4);
        ASSERT_TRUE(bst.min() == t3);
        BinarySearchTree::TaskItem t5(10001, "Take out garbage");
        bst.insert(t5);
        ASSERT_TRUE(bst.exists(t5));
        ASSERT_TRUE(bst.get_size() == 5);
        ASSERT_TRUE(bst.max() == t5);
        ASSERT_TRUE(bst.min() == t3);
        //test remove of last inserted value
        ASSERT_TRUE(bst.remove(t5));
        ASSERT_FALSE(bst.exists(t5));
        ASSERT_FALSE(bst.remove(t5));
        ASSERT_TRUE(bst.get_size() == 4);
        ASSERT_TRUE(bst.max() == t4);
        ASSERT_TRUE(bst.min() == t3);
        //test remove of middle value
        ASSERT_TRUE(bst.exists(t3));
        ASSERT_TRUE(bst.remove(t3));
        ASSERT_FALSE(bst.exists(t3));
        ASSERT_FALSE(bst.remove(t3));
        ASSERT_TRUE(bst.get_size() == 3);
        ASSERT_TRUE(bst.max() == t4);
        ASSERT_TRUE(bst.min() == t2);
        //test remove of first value
        ASSERT_TRUE(bst.exists(t1));
        ASSERT_TRUE(bst.remove(t1));
        ASSERT_FALSE(bst.exists(t1));
        ASSERT_FALSE(bst.remove(t1));
        ASSERT_TRUE(bst.get_size() == 2);
        ASSERT_TRUE(bst.max() == t4);
        ASSERT_TRUE(bst.min() == t2);
        BinarySearchTree::TaskItem t6(93, "Take out recycling");
        bst.insert(t6);
        ASSERT_TRUE(bst.get_size() == 3);
        BinarySearchTree::TaskItem t7(7000, "Wash counter");
        bst.insert(t7);
        ASSERT_TRUE(bst.get_size() == 4);
        ASSERT_TRUE(bst.max() == t7);
        ASSERT_TRUE(bst.min() == t2);
        BinarySearchTree::TaskItem t8(8, "Wash hands");
        bst.insert(t8);
        ASSERT_TRUE(bst.get_size() == 5);
        //test remove to empty
        ASSERT_TRUE(bst.remove(t8));
        ASSERT_TRUE(bst.get_size() == 4);
        ASSERT_TRUE(bst.remove(t7));
        ASSERT_TRUE(bst.max() == t4);
        ASSERT_TRUE(bst.min() == t2);
        ASSERT_TRUE(bst.get_size() == 3);
        ASSERT_TRUE(bst.remove(t6));
        ASSERT_TRUE(bst.get_size() == 2);
        ASSERT_TRUE(bst.remove(t4));
        ASSERT_TRUE(bst.max() == t2);
        ASSERT_TRUE(bst.min() == t2);
        ASSERT_TRUE(bst.get_size() == 1);
        ASSERT_TRUE(bst.remove(t2));
        ASSERT_TRUE(bst.get_size() == 0);
        ASSERT_TRUE(bst.max() == empt);
        ASSERT_TRUE(bst.min() == empt);
        ASSERT_FALSE(bst.remove(t5));
        return true;
    }
};

#endif
