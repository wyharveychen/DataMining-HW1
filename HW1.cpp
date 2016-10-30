#include<iostream>
#include"TidsetMgr.h"

int main(int argc, char* argv[]){
    assert(argc == 2 && "must read one data!");
    TidsetMgr tmgr;
    tmgr.ReadRawInput(argv[1]);
    return 0;
}

/*
int IntersectTid(bool* t1, bool* t2, bool* to, size_t t_size){
    int count = 0;
    for(size_t i = 0; i< t_size; i++){
        to[i] = t1[i] & t2[i];                    
        count += to[i];
    }   
}
*/
