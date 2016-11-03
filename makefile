CC = g++ 
CFLAGS = -g -DDEBUG_FLAG
all: HW1.cpp TidsetMgr.cpp TidsetMgr.h TidsetNode.h SetStruct.h
	$(CC) -o HW1 HW1.cpp TidsetMgr.cpp
debug: HW1.cpp TidsetMgr.cpp TidsetMgr.h TidsetNode.h SetStruct.h
	$(CC) $(CFLAGS) -o HW1 HW1.cpp TidsetMgr.cpp 
clean:
	rm -f HW1

