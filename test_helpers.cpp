#include "test_helpers.hpp"


/*
 * All these funtions are essentially the same, I could've made them into one function but i was tired
 * These functions are where threads start for the algorithm, they write their chuck of data to a shared resource
 * using the algorithm specified. When they all do that they each pop the same number of data they entered into
 * the shared resource
 *
 * Lifo lock test just has all the threads write to a shared vector, but we lock it using the lifo lock.
 *
 * Last function creates a vector of vectors of positive integers
 */

void enter_data_treiber(int tid, vector<vector<int>> data, barrier<> *b, Treiber* t, bool test){
    b->arrive_and_wait();
    if(tid == 0 && test){
        cout << " Treiber Stack" << endl;
        cout << "-------------------" << endl;
        cout << "Pushing" << endl;
    }
    b->arrive_and_wait();
    for(int i = 0; i < int(data[tid].size());i++){
        t->push(data[tid][i]);
    }
    b->arrive_and_wait();
    if(tid == 0 && test){
        cout << " " << endl;
        cout << "Popping" << endl;
    }
    b->arrive_and_wait();
    for(int i = 0; i < int(data[tid].size());i++){
        t->pop();
    }
    b->arrive_and_wait();
}

void enter_data_ms(int tid, vector<vector<int>> data, barrier<> *b, MSQueue* m, bool test){
    b->arrive_and_wait();
    if(tid == 0 && test){
        cout << " MS Queue " << endl;
        cout << "-------------------" << endl;
        cout << "Pushing" << endl;
    }
    b->arrive_and_wait();
    for(int i = 0; i < int(data[tid].size());i++){
        m->enqueue(data[tid][i]);
    }
    b->arrive_and_wait();
    if(tid == 0 && test){
        cout << " " << endl;
        cout << "Popping" << endl;
    }
    b->arrive_and_wait();
    for(int i = 0; i < int(data[tid].size());i++){
        m->dequeue();
    }
    b->arrive_and_wait();
}

void enter_data_sgl_queue(int tid, vector<vector<int>> data, barrier<> *b, SQL_Queue* s, bool test){
    b->arrive_and_wait();
    if(tid == 0 && test){
        cout << "SGL Queue " << endl;
        cout << "-------------------" << endl;
        cout << "Pushing" << endl;
    }
    b->arrive_and_wait();
    for(int i = 0; i < int(data[tid].size());i++){
        s->enqueue(data[tid][i]);
    }
    b->arrive_and_wait();
    if(tid == 0 && test){
        cout << " " << endl;
        cout << "Popping" << endl;
    }
    b->arrive_and_wait();
    for(int i = 0; i < int(data[tid].size());i++){
        s->dequeue();
    }
    b->arrive_and_wait();
}

void enter_data_sgl_stack(int tid, vector<vector<int>> data, barrier<> *b, SQL_Stack* s, bool test){
    b->arrive_and_wait();
    if(tid == 0 && test){
        cout << "SGL Stack" << endl;
        cout << "-------------------" << endl;
        cout << "Pushing" << endl;
    }
    b->arrive_and_wait();
    for(int i = 0; i < int(data[tid].size());i++){
        s->push(data[tid][i]);
    }
    b->arrive_and_wait();
    if(tid == 0 && test){
        cout << " " << endl;
        cout << "Popping" << endl;
    }
    b->arrive_and_wait();
    for(int i = 0; i < int(data[tid].size());i++){
        s->pop();
    }
    b->arrive_and_wait();
}

void run_lifo_lock(int tid, vector<vector<int>> data, barrier<>* b, Locks* lk, vector<int>* res, bool test){
    for(int i = 0; i < int(data[tid].size());i++){
        lk->acquire();
        res->push_back(data[tid][i]);
        lk->release();
    }
    b->arrive_and_wait();
}



vector<vector <int>> create_data(int size, int NUMTHREADS){
    vector<vector<int>> tmp_vect;
    if (size < NUMTHREADS){
        cout << "Too many threads" << endl;
        return tmp_vect;
    }
    int tmp_size = size/NUMTHREADS;
    // cout << "Original Vector: ";
    for(int i = 0; i < NUMTHREADS; i++){
        vector <int> thread_vect;
        if(i == NUMTHREADS - 1){
            tmp_size = size - (tmp_size * (NUMTHREADS-1));
        }
        for(int j = 0; j < tmp_size; j++){
            int tmp_n = rand() % 30;
            thread_vect.push_back(tmp_n);
            // printf("%d ", tmp_n);
        }
        tmp_vect.push_back(thread_vect);
    }
    // cout << " " <<endl;
    return tmp_vect;
}
