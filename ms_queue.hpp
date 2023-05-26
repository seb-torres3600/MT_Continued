#include <iostream>
#include <atomic>

using namespace std;

#define CAS compare_exchange_strong
#define DUMMY 0

class MSQueue{
    public:
        // node class for msqueue
        class node{
            public:
                node(int v):val(v){}
                int val;
                atomic<node*> next;
        };
        // testing boolean
        bool testing;
        MSQueue(bool test);
        void enqueue(int value);
        int dequeue();
        atomic<node*> head;
        atomic<node*> tail;
};