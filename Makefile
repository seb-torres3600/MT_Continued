CXX = g++
CXXFLAGS = -pthread -O3 -std=c++2a -g -Wall -Wextra

all: main

clean:
	rm read_write.o lifo_locks.o ms_queue.o sgl_queue.o sgl_stack.o treiber.o test_helpers.o concurrent_data_struct test

main: read_write.o lifo_locks.o ms_queue.o sgl_queue.o sgl_stack.o treiber.o test_helpers.o test.cpp main.cpp
	$(CXX) $(CXXFLAGS) main.cpp read_write.o lifo_locks.o ms_queue.o sgl_queue.o sgl_stack.o treiber.o test_helpers.o -o concurrent_data_struct
	$(CXX) $(CXXFLAGS) test.cpp read_write.o lifo_locks.o ms_queue.o sgl_queue.o sgl_stack.o treiber.o test_helpers.o -o test

read_write.o: read_write.cpp
	$(CXX) $(CXXFLAGS) -c read_write.cpp

lifo_locks.o: lifo_locks.cpp
	$(CXX) $(CXXFLAGS) -c lifo_locks.cpp

ms_queue.o: ms_queue.cpp
	$(CXX) $(CXXFLAGS) -c ms_queue.cpp

sgl_queue.o: sgl_queue.cpp
	$(CXX) $(CXXFLAGS) -c sgl_queue.cpp

sgl_stack.o: sgl_stack.cpp
	$(CXX) $(CXXFLAGS) -c sgl_stack.cpp

treiber.o: treiber.cpp
	$(CXX) $(CXXFLAGS) -c treiber.cpp

test_helpers.o: test_helpers.cpp
	$(CXX) $(CXXFLAGS) -c test_helpers.cpp

