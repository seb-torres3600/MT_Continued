#include "sgl_stack.hpp"

// create lock and set testing boolean
SQL_Stack :: SQL_Stack(bool test){
    lk  = new mutex();
    testing = test;
}

// delete lock
SQL_Stack ::~SQL_Stack() {
    delete lk;
}

// lock stack,pop, then unlock
void SQL_Stack ::pop() {
    lk->lock();
    while(!sql_s.empty()) {
        if(testing){ printf("%d ", sql_s.top());}
        sql_s.pop();
    }
    lk->unlock();
}

// lock stack, push value then unlock
void SQL_Stack :: push(int value){
    lk->lock();
    sql_s.push(value);
    if(testing){ printf("%d ", sql_s.top());}
    lk->unlock();
}

