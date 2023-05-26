#include <iostream>
#include <barrier>
#include "ms_queue.hpp"
#include "sgl_queue.hpp"
#include "sgl_stack.hpp"
#include "treiber.hpp"
#include "lifo_locks.hpp"
#include "read_write.hpp"


void enter_data_treiber(int tid, vector<vector<int>> data, barrier<> *b, Treiber* t, bool test);
void enter_data_ms(int tid, vector<vector<int>> data, barrier<> *b, MSQueue* m, bool test);
void enter_data_sgl_queue(int tid, vector<vector<int>> data, barrier<> *b, SQL_Queue* s, bool test);
void enter_data_sgl_stack(int tid, vector<vector<int>> data, barrier<> *b, SQL_Stack* s, bool test);
void run_lifo_lock(int tid, vector<vector<int>> data, barrier<>* b, Locks *lk, vector<int>* res, bool test);
vector <vector<int>> create_data(int size, int NUMTHREADS);

