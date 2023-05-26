#include "ms_queue.hpp"

// implemented from lecture slides

MSQueue ::MSQueue(bool test) {
    node* dummy = new node(DUMMY);
    head.store(dummy);
    tail.store(dummy);
    testing = test;
}
// enqueue
void MSQueue::enqueue(int value) {
    node *t, *e, *n, *dummy = NULL;
    // get a new node
    n = new node(value);
    while (true){
        //load tail data
        t = tail.load();
        // load next data
        e = t->next.load();
        if(t == tail.load()){
            // compare and exhange for dummy node
            if(e == NULL && t->next.CAS(dummy,n)){break;}
            // compare and exhange next node
            else if(e != NULL){tail.CAS(t,e);}
        }
    }
    //compare and exchange tail and our new val
    tail.CAS(t,n);
    //for testing
    if(testing){ printf("%i ", n->val);}
}
//dequeue
int MSQueue ::dequeue() {
    node *t, *h, *n = NULL;
    while(true){
        // load head
        h = head.load();
        //load tail
        t = tail.load();
        //load next val
        n = h->next.load();
        if(h == head.load()){
            // if head and tail are the same
            if(h == t){
                // if next val is node return NULL
                if(n == NULL){return NULL;}
                // else compare exhange tail and next val
                else{tail.CAS(t,n);}
            }
            else{
                // get result
                int res = n->val;
                //compare exchange head and next and return res value
                if(head.CAS(h,n)){
                    if(testing){ printf("%i ", res);}
                    return res;
                }
            }
        }
    }
}