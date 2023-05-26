#include "sgl_queue.hpp"

// create lock and set testing bool
SQL_Queue :: SQL_Queue(bool test) {
    lk = new mutex();
    testing = test;
}

// delete lock
SQL_Queue :: ~SQL_Queue() {
    delete lk;
}

// lock queue and pop then unlock
void SQL_Queue :: dequeue() {
    lk->lock();
    // if not empty
    while(!sgl_q.empty()){
        // testing print
        if(testing){printf("%d ", sgl_q.front());}
        sgl_q.pop();
    }
    lk->unlock();
}
// lock queue, add value, unlock
void SQL_Queue :: enqueue(int value) {
    lk->lock();
    sgl_q.push(value);
    if(testing){printf("%d ", sgl_q.back());}
    lk->unlock();
}
