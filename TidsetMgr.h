#ifndef TIDSETMGR
#define TIDSETMGR

#include<fstream>
#include<sstream>
#include<string>
#include<stdio.h> 
#include<stdlib.h> 
#include<assert.h>
#include<vector>
#include<map>
#include<algorithm>

#define DEBUG 1
using namespace std;

class TidsetMgr
{
public:
    TidsetMgr(){ _tid_num = 0;}
    ~TidsetMgr(){}

    //void ReadInput(char* filename);
    void ReadRawInput(char* filename);
    void Eclact(int depth);

    static void IntersectTid(vector<int>* t1, vector<int>* t2, vector<int>* to);

    map<int, vector<int>* >     _tidsetp_list;
    map<string, int>            _tid_map;
    int                         _tid_num;
    
};


#endif
