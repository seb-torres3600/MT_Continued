#include "lifo_locks.hpp"

// constructor
Locks ::Locks() {
    my_lock = new Lock_struct;
    my_node = new Lock_struct;
}

Locks ::~Locks() {
    delete my_lock;
    delete my_node;
}

void Locks ::acquire() {
    // push node that got acquire to stack
    my_lock->sta.push(my_node);
    // if stack is just the current node, then we have the lock
    if(my_lock->sta.size() == 1){
        return;
    }
    else{
        // store that my node is locked
        my_node->locked.store(true,memory_order_relaxed);
        // spin lock wait
        while(my_node->locked.load(memory_order_acquire)){}
    }
}

void Locks ::release() {
    // pop off stack
    my_lock->sta.pop();
    // if we still have threads waiting
    if(my_lock->sta.size() > 0){
        // get next thread info
        Lock_struct* next_thread = my_lock->sta.top();
        next_thread->locked.store(false,memory_order_relaxed);
    }
}

