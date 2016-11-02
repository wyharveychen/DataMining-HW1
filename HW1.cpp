#include<iostream>
#include<ctime>
#include"TidsetMgr.h"

int main(int argc, char* argv[]){
    assert(argc == 2 && "must read one data!");
    TidsetMgr tmgr;
    printf("Reading File...\n");
    tmgr.ReadRawInput(argv[1]);

    float sup = 0.0005;
    int max_depth = 64;
    string method_list[2] = {"Tid","Bit"};
    for(int m_i = 0; m_i<2; m_i++){
        printf("Performing Eclact %s... sup = %f\n",method_list[m_i].c_str(),sup);
        clock_t c_start = clock();        
        tmgr.Eclact(method_list[m_i], sup, max_depth);
        clock_t c_end = clock();        
        tmgr.PrintResult("result.txt");
        printf("Eclact time: %f s\n", (double)(c_end-c_start)/ CLOCKS_PER_SEC);
    }
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
