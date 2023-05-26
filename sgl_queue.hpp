#include <iostream>
#include <mutex>
#include <queue>

using namespace std;

class SQL_Queue{
    private:
        mutex* lk;
        queue<int> sgl_q;
        bool testing;
    public:
        SQL_Queue(bool test);
        ~SQL_Queue();
        void dequeue();
        void enqueue(int value);
};

