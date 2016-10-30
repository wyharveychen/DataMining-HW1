#include"TidsetMgr.h"


void TidsetNode::InitTidset(map<int, vector<int>* >* tidsetp_listp, int minsup, int maxdepth){
    //depend: _mgr->minsup, _mgr->maxdepth    

    //map<int, vectorint<int>*> tidsetp_listp->= *tidsetp_listp->;

    vector<int>* presetp;
    vector<int>* tidsetp;
        
    for(map<int,vector<int>*>::iterator it = tidsetp_listp->begin(); it != tidsetp_listp->end(); ++it ){
        if(it == tidsetp_listp->begin()){
            _prefix.push_back(it->first);
            if(_prefix.size() == maxdepth)
                return;
            presetp  = it->second;
            continue;
        }

        int item = it->first;
        
        tidsetp = it->second;
        
        vector<int>* subsetp = new vector<int>();
        TidsetMgr::IntersectTid(presetp,tidsetp,subsetp);

        if(subsetp->size() >  minsup){
            _subsetp_list.insert(pair<int,vector<int>*>(item,subsetp));
            if(DEBUG){
                for(int i=0;i<_prefix.size();i++){
                    printf("{%d} ", _prefix[i]);
                }
                printf("{%d} : %d\n",item,(int)subsetp->size());
            }
        }
    }

    map<int,vector<int>*>  subsetp_list(_subsetp_list);

    while(subsetp_list.size() != 0){ 
        TidsetNode* subnodep = new TidsetNode(_prefix);
        _subnodep_list.push_back(subnodep);
        subnodep->InitTidset(&subsetp_list, minsup, maxdepth);

        subsetp_list.erase(subsetp_list.begin());
    }   
       

}
