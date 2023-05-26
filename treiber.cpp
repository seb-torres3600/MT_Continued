#include "treiber.hpp"

// set testing bool
Treiber::Treiber(bool testing) {
    test = testing;
}

void Treiber ::push(int value) {
    // create new node
    node* n = new node(value);
    node* t;
    do{
        // load top
        t = top.load(ACQ);
        // set one down to prev top val
        n->down = t;
        if(test) printf("%i ", n->val);
        // compare exchange top and new value
    }while(!top.CAS(t,n,ACQREL));
}

int Treiber ::pop() {
    node *t,*n = NULL;
    int v;
    do{
        //load top
        t = top.load(ACQ);
        // if nothing, return null
        if(t == NULL){ return NULL;}
        // next is top minus one
        n = t->down;
        // our value is top val
        v = t->val;
        if(test) printf("%i ", v);
        // compare exhange top, next
    } while (!top.CAS(t,n,ACQREL));
    //return pop value
    return v;
}