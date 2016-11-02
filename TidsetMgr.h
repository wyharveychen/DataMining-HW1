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
#include"TidsetNode.h"

using namespace std;


class TidsetMgr
{
public:
    TidsetMgr(){ 
        _tid_num = 0;    
    }
    ~TidsetMgr(){}

    void ReadRawInput(char* filename);
    void Eclact(string method, float minsupr, int maxdepth);
    void PrintResult(string filename = "");

    map<int, TidS* >                _tidsetp_list;
    map<int, BitS* >                _bitsetp_list; 
//    vector<TidsetNode<TidS >*>      _tidsnodep_list;
//    vector<TidsetNode<BitS >*>      _tidsnodep_list;
    vector<ItemSup>               _itemsup_list;

    map<string, int>            _tid_map;
    int                         _tid_num;
};

#endif
