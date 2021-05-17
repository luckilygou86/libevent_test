SRC=./*.cpp
INCLUDE=../include/test_thread_pool_in
LIB=../lib
test_thread_poll:$(SRC)
	g++ $^ -g -o $@ -I $(INCLUDE) -L $(LIB) -levent -lpthread -std=c++11
	./$@
clean:
	rm -rf test_thread_pool
	rm -rf *.o

