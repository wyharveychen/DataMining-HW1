#ifndef SETSTRUCT
#define SETSTRUCT

#include<stdio.h> 
#include<stdlib.h> 
#include<vector>
#include<map>
#include<algorithm>
#include<bitset>
#include<set>

using namespace std;

class TidS: public vector<int>{
public:
    size_t count(){
        return this->size();
    }

    static void IntersectSet(TidS* t1, TidS* t2, TidS* to){
    // assume t1 and t2 are sorted
        int i1 = 0;
        int i2 = 0;
        while(i1 < t1->size() && i2 < t2->size()){
            if((*t1)[i1] == (*t2)[i2]){
                to->push_back((*t1)[i1]); //either is OK        
                i1++; i2++;
            }else if((*t1)[i1] < (*t2)[i2]){
                i1++;
            }else{
                i2++;
            }        
        }
        return;
    }

};

class BitS: public bitset<3600000>{
public:   
    static void IntersectSet(BitS* b1, BitS* b2, BitS* bo){
        (*bo) = (*b1);
        (*bo) &= (*b2);                     
        return;
    }
};

#endif
