test_server:./src/test_server.cpp
	g++ $^ -o $@ -levent
	./$@
clean:
	rm -rf first_libevent
	rm -rf *.o