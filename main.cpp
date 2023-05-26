/*
Sebastian Torres
12/1/2022
*/

#include <iostream>
#include <thread>
#include <unistd.h>
#include <getopt.h>
#include "read_write.hpp"
#include "test_helpers.hpp"

using namespace std;

int main(int argc, char** argv){

    // Variable declarations
    int our_option;
    // Num of threads defaults to 4 if nothing passed
    int  NUM_THREADS = 4;
    string alg_type;
    // default vector size as 20
    int vector_size = 20;
    // default to not testing
    bool testing = false;
    // get source file
    if (argc == 1){
        cout << "Atleast pick an algorithm to run" << endl;
        print_usage();
        return 0;
    }

    // Creating the long options
    static struct option long_options[] = {
            {"name",   no_argument,         0,  'n' },
            {"alg",   required_argument,   0,  'a' },
            {"testing",   required_argument,   0,  'w' },
            {0, 0, 0, 0}
    };

    // get all arguments
    while(1) {
        int index = 0;
        our_option = getopt_long(argc, argv, "n:a:t:i:v:hw:",long_options, &index);

        // When all the options have been read
        if (our_option == -1) {
            break;
        }

        switch(our_option) {

            // Name option. Program will terminate after printing name.
            case 'n': {

                cout << "Sebastian Torres" << endl;
                return 0;

            }
            // testing flag
            case 'w':{
                string tmp = optarg;
                if(tmp == "true"){
                    testing = true;
                }
                break;
            }
            // help
            case 'h':{
                print_usage();
                return 0;
            }

                // Choose alg type
            case 'a': {

                alg_type = optarg;

                if(alg_type != "treiber" && alg_type != "sglstack" && alg_type != "sglqueue" && alg_type != "msqueue" && alg_type != "lifolock"){
                    cout << "Alg Unknown" << endl;
                    print_usage();
                    return -1;
                }

                break;

            }
            //vector size
            case 'v':{
                vector_size = atoi(optarg);
                break;
            }

                // Number of threads
            case 't': {

                NUM_THREADS = atoi(optarg);
                if(NUM_THREADS > 150){
                    cout << "ERROR; too many threads\n" << endl;
                    return -1;
                }

                break;

            }

        }

    }
    // get vector of vectors so that threads can have their own info to run
    // create data creates vector of random numbers
    vector<vector <int>> our_data = create_data(vector_size, NUM_THREADS);
    vector<thread*> threads;
    threads.resize(NUM_THREADS);
    barrier<> *bar;
    bar = new barrier(NUM_THREADS);
    int i;

    if(alg_type == "treiber"){
            // TREIBER Testing
            Treiber triber_test((testing));
            for(i = 1; i < NUM_THREADS; i++){
                threads[i] = new thread(enter_data_treiber,i,our_data, bar, &triber_test, testing);
            }
            i = 0;
            enter_data_treiber(i, our_data, bar, &triber_test, testing);
            // join threads
            for( i=1; i<NUM_THREADS; i++){
                threads[i]->join();
                delete threads[i];
            }
            cout << "" << endl;
    }
    else if(alg_type == "msqueue"){
            // MS QUEUE TESTING
            MSQueue ms_test((testing));
            for(i = 1; i < NUM_THREADS; i++){
                threads[i] = new thread(enter_data_ms,i,our_data, bar, &ms_test, testing);
            }
            i = 0;
            enter_data_ms(i,our_data, bar, &ms_test, testing);
            // join threads
            for( i=1; i<NUM_THREADS; i++){
                threads[i]->join();
                delete threads[i];
            }
            cout << "" << endl;
    }
    else if(alg_type == "sglqueue"){
            // SGL queue
            SQL_Queue sgl_q(testing);
            for(i = 1; i < NUM_THREADS; i++){
                threads[i] = new thread(enter_data_sgl_queue,i,our_data, bar, &sgl_q, testing);
            }
            i = 0;
            enter_data_sgl_queue(i,our_data, bar, &sgl_q, testing);
            // join threads
            for( i=1; i<NUM_THREADS; i++){
                threads[i]->join();
                delete threads[i];
            }
            cout << "" << endl;
    }
    else if(alg_type == "sglstack"){
            // SGL stack
            SQL_Stack sgl_s(testing);
            for(i = 1; i < NUM_THREADS; i++){
                threads[i] = new thread(enter_data_sgl_stack,i,our_data, bar, &sgl_s, testing);
            }
            i = 0;
            enter_data_sgl_stack(i,our_data, bar, &sgl_s, testing);
            // join threads
            for( i=1; i<NUM_THREADS; i++){
                threads[i]->join();
                delete threads[i];
            }
            cout << "" << endl;
    }
    else if(alg_type == "lifolock"){
        Locks lk;
        vector <int> empty;
        for(i = 1; i < NUM_THREADS; i++){
            threads[i] = new thread(run_lifo_lock,i,our_data, bar, &lk, &empty, testing);
        }
        i = 0;
        run_lifo_lock(i,our_data, bar, &lk, &empty, testing);
        // join threads
        for( i=1; i<NUM_THREADS; i++){
            threads[i]->join();
            delete threads[i];
        }
        if(testing){
            cout << "Lifo Lock" << endl;
            cout << "-----------" << endl;
            print(empty);
        }
    }
    else{
        cout << "Check inputs, something went wrong" << endl;
        print_usage();
    }
    delete bar;
    if (testing == false){
        cout << "Turn on testing to see output" << endl;
        print_usage();
    }
    return 0;
}

