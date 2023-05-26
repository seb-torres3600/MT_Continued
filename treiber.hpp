#include <iostream>
#include <mutex>
#include <atomic>

using namespace std;
#define ACQ memory_order_acquire
#define ACQREL memory_order_acq_rel
#define CAS compare_exchange_strong

class Treiber{
    public:
        class node{
            public:
                node(int v):val(v){}
                int val;
                node* down;
            };
        Treiber(bool testing);
        void push(int value);
        int pop();
    private:
        atomic<node*> top;
        bool test;
};