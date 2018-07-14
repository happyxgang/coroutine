test: coctx_swap.S coroutine.cpp test.cpp coroutine.h 
	 gcc -c coctx_swap.S  -m32 -g
	 g++ -c coroutine.cpp -m32 -g
	 g++ test.cpp coctx_swap.o coroutine.o -m32 -g -o test

