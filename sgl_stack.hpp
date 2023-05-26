#include <iostream>
#include <mutex>
#include <stack>

using namespace std;

class SQL_Stack{
    private:
        mutex* lk;
        stack<int> sql_s;
        bool testing;

    public:
        SQL_Stack(bool test);
        ~SQL_Stack();
        void push(int value);
        void pop();
};