#ifndef TIDSETNODE
#define TIDSETNODE

#include<stdio.h> 
#include<stdlib.h> 
#include<vector>
#include<map>
#include<set>
#include<algorithm>
#include"SetStruct.h"

using namespace std;

typedef vector<int> IntL;
typedef set<int> IntS;
typedef pair<IntL,size_t> ItemSup;


template<class T>
class TidsetNode
{
public:
    TidsetNode(IntL prefix){ _prefix = prefix;}
    ~TidsetNode(){ 
        for(typename map<int,T*>::iterator it = _subsetp_list.begin(); it != _subsetp_list.end(); ++it ){
            delete it->second;        
        }
    }
    
    void RecurEclact(map<int, T* >* set_listp, vector<ItemSup>* itemsup_listp,int minsup, int maxdepth);

    IntL _prefix;   
    
    map<int, T* >           _subsetp_list;
//    vector<TidsetNode*>     _subnodep_list;
};
#endif
template<class T>
void TidsetNode<T>::RecurEclact(map<int, T* >* setp_listp,  vector<ItemSup>* itemsup_listp , int minsup, int maxdepth){
    T* presetp;
    T* setp;
        
    for(typename map<int,T*>::iterator it = setp_listp->begin(); it != setp_listp->end(); ++it ){
        if(it == setp_listp->begin()){
            _prefix.push_back(it->first);
            if(_prefix.size() == maxdepth)
                return;
            presetp  = it->second;         
        }else{
            int item = it->first;            
            setp = it->second;
            
            T* subsetp = new T();
            T::IntersectSet(presetp,setp,subsetp);

            if(subsetp->count() >  minsup){
                _subsetp_list.insert(pair<int,T*>(item,subsetp));
                IntL items = _prefix;
                items.push_back(item);
                itemsup_listp->push_back(ItemSup(items,subsetp->count()));
                #ifdef DEBUG_FLAG
                    for(int i=0;i<_prefix.size();i++){
                        printf("{%d} ", _prefix[i]);
                    }
                    printf("{%d} : %d\n",item,(int)subsetp->count());
                #endif
            }
        }
    }

    map<int,T*>  subsetp_list(_subsetp_list);

    while(subsetp_list.size() != 0){ 
        TidsetNode* subnodep = new TidsetNode(_prefix);
        //_subnodep_list.push_back(subnodep);
        subnodep->RecurEclact(&subsetp_list, itemsup_listp,minsup, maxdepth);        
        subsetp_list.erase(subsetp_list.begin());
        delete subnodep;
    }          
}
