
# A Makefile to build our 'haversine' project

C11     =  cc -std=c11
CFLAGS  =  -Wall -pedantic -Werror

mysync : mysync.o compare_files.o
	$(C11) $(CFLAGS) -o mysync \
		mysync.o compare_files.o -lm

mysync.o : mysync.c mysync.h
	$(C11) $(CFLAGS) -c mysync.c

compare_files.o : compare_files.c mysync.h
	$(C11) $(CFLAGS) -c compare_files.c

clean:
	rm -rf mysync *.o
