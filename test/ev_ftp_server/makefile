SRC=./*cpp
INCLUDE=../include/ev_ftp_in
ev_ftp_server:$(SRC)
	g++ $^ -g -o $@ -I $(INCLUDE) -L../lib -levent -lpthread --std=c++11
	gdb ./$@
clean:
	rm -rf ev_ftp_server
	rm -rf *.o

