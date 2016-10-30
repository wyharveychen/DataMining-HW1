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

class TidsetNode
{
public:
    TidsetNode(vector<int> prefix){ _prefix = prefix;}


    void InitTidset(map<int, vector<int>* >* tidset_listp, int minsup, int maxdepth);


    vector<int> _prefix;   
    
    map<int, vector<int>* >     _subsetp_list;
    vector<TidsetNode*>         _subnodep_list;

};

class TidsetMgr
{
public:
    TidsetMgr(){ _tid_num = 0; _minsup = 0; _maxdepth = 4;}
    ~TidsetMgr(){}

    void ReadRawInput(char* filename);
    void Eclact();

    static void IntersectTid(vector<int>* t1, vector<int>* t2, vector<int>* to);

    map<int, vector<int>* >     _tidsetp_list;
    vector<TidsetNode*>         _subnodep_list;


    map<string, int>            _tid_map;
    int                         _tid_num;

    int                         _minsup;
    int                         _maxdepth;    
};

#endif
