#include <iostream>
#include <thread>
#include "test_helpers.hpp"

using namespace std;

int main(int argc, const char* argv[]){
    int NUM_THREADS;
    int vector_size;
    if (argc == 3){
        NUM_THREADS = atoi(argv[1]);
        vector_size = atoi(argv[2]);
    }
    else if(argc == 1){
        NUM_THREADS = 4;
        vector_size = 20;
    }
    else{
        cout << "Usage: ./test NUM_THREADS TEST_VECTOR_SIZE" << endl;
        cout << "Or ./test if you want to 4 threads, vector size of 20, for all" << endl;
        cout << "Example: ./test 4 12 " << endl;
        return -1;
    }
    vector<vector <int>> our_data = create_data(vector_size, NUM_THREADS);
    vector<thread*> threads;
    threads.resize(NUM_THREADS);
    barrier<> *bar;
    bar = new barrier(NUM_THREADS);
    int i;
    bool test = true;

    // TREIBER Testing
    Treiber triber_test((true));
    for(i = 1; i < NUM_THREADS; i++){
        threads[i] = new thread(enter_data_treiber,i,our_data, bar, &triber_test,test);
    }
    i = 0;
    enter_data_treiber(i, our_data, bar, &triber_test,test);
    // join threads
    for( i=1; i<NUM_THREADS; i++){
        threads[i]->join();
        delete threads[i];
    }
    cout << "" << endl;

    // MS QUEUE TESTING NOW
    MSQueue ms_test((true));
    for(i = 1; i < NUM_THREADS; i++){
        threads[i] = new thread(enter_data_ms,i,our_data, bar, &ms_test,test);
    }
    i = 0;
    enter_data_ms(i,our_data, bar, &ms_test,test);
    // join threads
    for( i=1; i<NUM_THREADS; i++){
        threads[i]->join();
        delete threads[i];
    }
    cout << "" << endl;

    // SGL queue
    SQL_Queue sgl_q(true);
    for(i = 1; i < NUM_THREADS; i++){
        threads[i] = new thread(enter_data_sgl_queue,i,our_data, bar, &sgl_q,test);
    }
    i = 0;
    enter_data_sgl_queue(i,our_data, bar, &sgl_q,test);
    // join threads
    for( i=1; i<NUM_THREADS; i++){
        threads[i]->join();
        delete threads[i];
    }
    cout << "" << endl;

    // SGL stack
    SQL_Stack sgl_s(true);
    for(i = 1; i < NUM_THREADS; i++){
        threads[i] = new thread(enter_data_sgl_stack,i,our_data, bar, &sgl_s,test);
    }
    i = 0;
    enter_data_sgl_stack(i,our_data, bar, &sgl_s,test);
    // join threads
    for( i=1; i<NUM_THREADS; i++){
        threads[i]->join();
        delete threads[i];
    }
    cout << "" << endl;

    cout << "Lifo Lock" << endl;
    cout << "------------" << endl;
    Locks lk;
    vector <int> empty;
    for(i = 1; i < NUM_THREADS; i++){
        threads[i] = new thread(run_lifo_lock,i,our_data, bar, &lk, &empty,test);
    }
    i = 0;
    run_lifo_lock(i,our_data, bar, &lk, &empty,test);
    // join threads
    for( i=1; i<NUM_THREADS; i++){
        threads[i]->join();
        delete threads[i];
    }
    print(empty);
    cout << "" << endl;
    delete bar;
    return 0;
}

