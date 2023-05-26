#include <iostream>
#include <atomic>
#include <stack>

using namespace std;

#define SEQ_CST memory_order_seq_cst
#define RELAXED memory_order_relaxed

class Locks{

public:
    // struct for stack
    struct Lock_struct{
        stack<Lock_struct*> sta;
        atomic<bool> locked;
    };
    Lock_struct* my_lock;
    Lock_struct* my_node;
    Locks();
    ~Locks();
    void acquire();
    void release();
};