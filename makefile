CC = g++ 
CFLAGS = -g 
all: HW1.cpp TidsetMgr.cpp TidsetMgr.h 
	$(CC) -o HW1.out HW1.cpp TidsetMgr.cpp 
debug: HW1.cpp TidsetMgr.cpp TidsetMgr.h 
	$(CC) $(CFLAGS) -o HW1.out HW1.cpp TidsetMgr.cpp 
clean:
	rm -f HW1.out

