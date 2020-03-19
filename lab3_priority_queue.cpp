#include "lab3_priority_queue.hpp"
#include <iostream>
using namespace std;

// PURPOSE: Parametric constructor 
// initializes heap to an array of (n_capacity + 1) elements
PriorityQueue::PriorityQueue(unsigned int n_capacity) {
    capacity = n_capacity;
    heap = new TaskItem* [capacity + 1];
    size = 0;
}

// PURPOSE: Explicit destructor of the class PriorityQueue
PriorityQueue::~PriorityQueue() {
    //remove all the elements inside the heap
    delete []heap;
}

// PURPOSE: Returns the number of elements in the priority queue
unsigned int PriorityQueue::get_size() const {
    return size;
}

// PURPOSE: Returns true if the priority queue is empty; false, otherwise
bool PriorityQueue::empty() const {
    return !size;
}

// PURPOSE: Returns true if the priority queue is full; false, otherwise
bool PriorityQueue::full() const {
    return size == capacity;
}

// PURPOSE: Prints the contents of the priority queue; format not specified
void PriorityQueue::print() const {
    for (int i = 1; i <= size; ++i) {
        cout << heap[i]->priority << "\t" << heap[i]->description << endl;
    }
}

// PURPOSE: Returns the max element of the priority queue without removing it
// if the priority queue is empty, it returns (-1, "N/A")
PriorityQueue::TaskItem PriorityQueue::max() const {
    if (empty()) {
        return TaskItem(-1, "N/A");
    }
    else {
        return *heap[1];
    }
}

// PURPOSE: Inserts the given value into the priority queue
// re-arranges the elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::enqueue( TaskItem val ) {
    if ( size == capacity)
        return false;
    if (empty()) {
        heap[1] = new TaskItem(val.priority, val.description);
    }
    bool dupl = false;
    for (int i = 1; i < size + 1; i++) {
        dupl = heap[i]->priority == val.priority;
    }
    if (dupl) {
        return false;
    } else {
        int i = size + 1;
        heap[i] = new TaskItem(val.priority, val.description);
        while (i > 1 && heap[i/2]->priority < heap[i]->priority) {
            TaskItem* temp = heap[i];
            heap[i] = heap[i/2];
            heap[i/2] = temp;
            i /= 2;
        }
    }
    size++;
    return true;
}

// PURPOSE: Removes the top element with the maximum priority
// re-arranges the remaining elements back into a heap
// returns true if successful and false otherwise
// priority queue does not change in capacity
bool PriorityQueue::dequeue() {
    if (empty())
        return false;
    if (size == 1) {
        delete heap[1];
        heap[1] = NULL;
    } else {
        TaskItem* temp = heap[1];
        heap[1] = heap[size];
        heap[size] = temp;

        delete heap[size];
        heap[size] = NULL;

        int i = 1;
        bool heap_valid = false;

        while ( i <= size && !heap_valid && (heap[2*i] || heap[2*i])) {
            int left_child_p = 0;
            int right_child_p = 0;
            TaskItem* left_child = heap[2*i];
            TaskItem* right_child = heap[2*i + 1];

            if (left_child)
                left_child_p = left_child->priority;

            if (right_child)
                right_child_p = right_child->priority;

            if (left_child_p < heap[i]->priority && right_child_p < heap[i]->priority)
                heap_valid = true;

            if (left_child_p >= right_child_p && left_child_p > heap[i]->priority) {
                heap[2*i] = heap[i];
                heap[i] = left_child;
            } else if (right_child_p > left_child_p && right_child_p > heap[i]->priority){
                heap[2*i + 1] = heap[i];
                heap[i] = right_child;
            }
            i++;
        }
    }
    size--;
    return true;
}
