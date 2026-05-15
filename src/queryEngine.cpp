#include "queryEngine.h"

void queryEngine::insert(string key, string value){

    
    Record r{key,value}; 

    if(bpm.getTotalPage() == 0){
        Page newPage;
    
        newPage.setID(0);
    
        newPage.insert(r);
        bpm.cachePage(newPage);
        bpm.incrementTotalPages();

    }
    else{//totalpages-1 = lastpage id
        Page &p = bpm.getPage(bpm.getTotalPage()-1);
        if(p.insert(r)){
            bpm.markDirty(bpm.getTotalPage()-1);
        }
        else{
            //new pageid == total pages
            Page newPage;
            newPage.setID(bpm.getTotalPage());
            newPage.insert(r);
            bpm.cachePage(newPage);
            bpm.incrementTotalPages();           
        }
    }
    
    
}

string queryEngine::search(string key){
    for(int i = 0; i < bpm.getTotalPage(); i++){
        Page &p = bpm.getPage(i);
        auto result = p.search(key);

        if (result.first){
            return result.second;
        }
        
    }
    return "NOT FOUND";
}
void queryEngine::remove(string key){
    for(int i = 0; i < bpm.getTotalPage(); i++){
        Page &p = bpm.getPage(i);
        if(p.remove(key)){
            bpm.markDirty(i);
            return;
        }
    }
}

void queryEngine::display(){
    for(int i = 0; i < bpm.getTotalPage(); i++){
        Page &p = bpm.getPage(i);
        for( auto &d : p.getRecords()){
            cout << p.getID() << endl;  //comment this line later - only for testing pageManager.
            cout << "(key:" << d.key << " value:" << d.value << ")";  
        }
    }
}

vector<Record> queryEngine::prefixSearch(string prefix){
    vector<Record> result;
    for(int i = 0; i < bpm.getTotalPage(); i++){
        Page &p = bpm.getPage(i);
        for(auto &r : p.getRecords()){
            if(r.key.substr(0,prefix.size()) == prefix){
                result.push_back(r);
            }
        }
    }
    return result;
}
 