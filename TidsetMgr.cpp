#include"TidsetMgr.h"
/*
void TidsetMgr::ReadInput(char* filename){
    string line;
    ifstream fi(filename);
    vector<int>* tidsetp;

    if(!fi.is_open())
        exit(EXIT_FAILURE);
    
    while(!fi.eof()){
        getline(fi,line);
        istringstream nums_str(line);
        int num = 0;
        tidsetp = new vector<int>();
        while( nums_str>>num){
            tidsetp->push_back(num);
        }
        _tidsetp_list.push_back(tidsetp);
    }
    if(DEBUG){
        for(int i = 0; i<_tidsetp_list.size(); i++){
            tidsetp = _tidsetp_list[i];
            for(int j = 0; j<tidsetp->size(); j++){
                printf("%d ",(*tidsetp)[j]);
            }
            printf("\n");
        }
    }
    return;
}
*/
void TidsetMgr::ReadRawInput(char* filename){
    string line;
    ifstream fi(filename);
    if(!fi.is_open())
        exit(EXIT_FAILURE);
    
    while(!fi.eof()){
        getline(fi,line);
        istringstream line_stream(line);
        string sub;
        char delim = ',';

        string tstr;
        int tid;

        for(int i  = 0; i < 3; i++){
            //It is known that, the input format is user,time,item

            if(!getline(line_stream, sub, delim))
                break;
            switch(i){
                case 0:{
                    tstr = sub; 
                    break;
                }case 1:{
                    tstr = tstr+sub;
                    if(_tid_map.count(tstr) == 0){
                        tid = _tid_num;
                        _tid_map.insert(pair<string,int>(tstr,tid));
                        _tid_num++;
                    }else{
                        tid = _tid_map[tstr];
                    }
                    break;
                }case 2:{
                    int item;
                    istringstream num_stream(sub);
                    num_stream >> item;
                    if(_tidsetp_list.count(item) == 0)            
                        _tidsetp_list.insert(pair<int, vector<int>*>(item, new vector<int>()) );                  
/*
                    while(_tidsetp_list.size()<item+1){
                        _tidsetp_list.push_back(NULL); //initialize until (item+1)th tidset 
                    }
                    if(_tidsetp_list[item] == NULL)
                        _tidsetp_list[item] = new vector<int>(); 
*/
                    _tidsetp_list[item]->push_back(tid);
                    break;
                }default:
                    exit(EXIT_FAILURE); //too many comma        
            }            
        }        
    }

    vector<int>* tidsetp;
    for(map<int,vector<int>*>::iterator it = _tidsetp_list.begin(); it != _tidsetp_list.end(); it++ ){
        tidsetp = it->second;
        sort(tidsetp->begin(),tidsetp->end());        
    }
    if(DEBUG){
        for(map<int,vector<int>*>::iterator it = _tidsetp_list.begin(); it != _tidsetp_list.end(); it++ ){
            tidsetp = it->second;            
            printf("item %d in ",it->first);
            for(int j = 0; j<tidsetp->size(); j++){
                printf("%d ",(*tidsetp)[j]);
            }
            printf("\n");
        }
    }
/*
    for(int i = 0; i<_tidsetp_list.size(); i++){
        tidsetp = _tidsetp_list[i];
        if(tidsetp == NULL)
            continue;
        sort(tidsetp->begin(),tidsetp->end());
    }
    if(DEBUG){
        for(int i = 0; i<_tidsetp_list.size(); i++){
            tidsetp = _tidsetp_list[i];
            if(tidsetp == NULL)
                continue;
            for(int j = 0; j<tidsetp->size(); j++){
                printf("%d ",(*tidsetp)[j]);
            }
            printf("\n");
        }
    }
*/
    return;
}

void TidsetMgr::Eclact(int depth){

}

void TidsetMgr::IntersectTid(vector<int>* t1, vector<int>* t2, vector<int>* to){
// assume t1 and t2 are sorted
    int i1 = 0;
    int i2 = 0;
    while(i1 < t1->size() && i1 <t2->size()){
        if((*t1)[i1] == (*t2)[i2]){
            to->push_back((*t1)[i1]); //either is OK        
        }else if((*t1)[i1] < (*t2)[i2]){
            i1++;
        }else{
            i2++;
        }        
    }
    return;
}
