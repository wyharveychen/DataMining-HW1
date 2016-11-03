#include"TidsetMgr.h"


void TidsetMgr::ReadRawInput(char* filename){
    string line;
    ifstream fi(filename);
    if(!fi.is_open())
        exit(EXIT_FAILURE);
    
    string sub;
    char delim = ',';

    string tstr;
    int tid = 0;
    #ifdef DEBUG_FLAG
        string prev_tstr;
        int line_num = 0;
    #endif
    while(!fi.eof()){
        getline(fi,line);
        istringstream line_stream(line);
        #ifdef DEBUG_FLAG
            line_num++;
        #endif

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
                        #ifdef DEBUG_FLAG
                            if(tstr.compare(prev_tstr) != 0){
                                printf("Duplicated line!%d\n",line_num);
                            }
                        #endif
                    }
                #ifdef DEBUG_FLAG
                    prev_tstr = tstr;
                #endif                    
                    break;
                }case 2:{
                    int item;
                    istringstream num_stream(sub);
                    num_stream >> item;
                    if(_tidsetp_list.count(item) == 0){            
                        _tidsetp_list.insert(pair<int, TidS*>(item, new TidS()) );                  
                        _bitsetp_list.insert(pair<int, BitS*>(item, new BitS()) );  
                    }
                    _tidsetp_list[item]->push_back(tid); 
                    (*_bitsetp_list[item])[tid] = 1;
                    break;
                }default:
                    exit(EXIT_FAILURE); //too many comma        
            }            
        }        
    }

    TidS* tidsetp;
    for(map<int,TidS*>::iterator it = _tidsetp_list.begin(); it != _tidsetp_list.end(); it++ ){
        tidsetp = it->second;
        sort(tidsetp->begin(),tidsetp->end());        
        int i = 0;
        
        while(i< tidsetp->size()-1){
            if((*tidsetp)[i] == (*tidsetp)[i+1])
                tidsetp->erase(tidsetp->begin()+i);
            else
                i++;
        }
        
    }
    
    #ifdef DEBUG_FLAG
        for(map<int,TidS*>::iterator it = _tidsetp_list.begin(); it != _tidsetp_list.end(); it++ ){
            tidsetp = it->second;            
            printf("item %d in ",it->first);
            for(int j = 0; j<tidsetp->size(); j++){
                printf("%d ",(*tidsetp)[j]);
            }
            printf("\n");
        }
    #endif
    return;
}


void TidsetMgr::Eclact(string method, float minsupr, int maxdepth){
    _itemsup_list.clear(); // clear restoration


    if(method.compare(string("Tid")) == 0){
        IntL prefix;
        for(map<int,TidS*>::iterator it = _tidsetp_list.begin(); it != _tidsetp_list.end(); it++ ){
            IntL items = prefix;
            items.push_back(it->first);
            _itemsup_list.push_back(ItemSup(items,it->second->count()));
            #ifdef DEBUG_FLAG
                printf("{%d} : %d\n",it->first,(int)it->second->count());
            #endif
        }
        TidS* tidsetp;
        map<int,TidS*>  sub_tidsetp_list(_tidsetp_list);   
        while(sub_tidsetp_list.size() != 0){ 
            TidsetNode<TidS>* subnode = new TidsetNode<TidS>(prefix);
            //_subnodep_list.push_back(subnode);
            subnode->RecurEclact(&sub_tidsetp_list, &_itemsup_list, _tid_num* minsupr, maxdepth);
            delete subnode;
            sub_tidsetp_list.erase(sub_tidsetp_list.begin());
        }
    }else if(method.compare(string("Bit")) == 0){
        IntL prefix;
        for(map<int,BitS*>::iterator it = _bitsetp_list.begin(); it != _bitsetp_list.end(); it++ ){
            IntL items = prefix;
            items.push_back(it->first);
            _itemsup_list.push_back(ItemSup(items,it->second->count()));
            #ifdef DEBUG_FLAG
                printf("{%d} : %d\n",it->first,(int)it->second->count());
            #endif
        }
        BitS* bitsetp;
        map<int,BitS*> sub_bitsetp_list(_bitsetp_list);
        while(sub_bitsetp_list.size() != 0){ 
            TidsetNode<BitS>* subnode = new TidsetNode<BitS>(prefix);
            //_subnodep_list.push_back(subnode);
            subnode->RecurEclact(&sub_bitsetp_list, &_itemsup_list, _tid_num* minsupr , maxdepth);
            delete subnode;
            sub_bitsetp_list.erase(sub_bitsetp_list.begin());
        }
    }else{
        printf("method error!");
        exit(EXIT_FAILURE);        
    }


}   

bool ItemSupComp(const ItemSup& is1, const ItemSup& is2){
    return is1.second > is2.second; //descend
}

void TidsetMgr::PrintResult(char* filename){
    sort(_itemsup_list.begin(),_itemsup_list.end(),ItemSupComp);
    if(filename  == NULL){        
        for(int i=0;i<_itemsup_list.size();i++) {
            ItemSup is = _itemsup_list[i];
            for(int j = 0;j<is.first.size();j++){
                printf("{%d} ",is.first[j]);
            }
            printf(": %d\n",(int)is.second);
        }
    }else{
        FILE * fp;
        fp = fopen(filename,"w");
        for(int i=0;i<_itemsup_list.size();i++) {
            ItemSup is = _itemsup_list[i];
            for(int j = 0;j<is.first.size();j++){
                fprintf(fp,"{%d} ",is.first[j]);
            }
            fprintf(fp,": %d\n",(int)is.second);
        }
        fclose(fp);
    }
}
