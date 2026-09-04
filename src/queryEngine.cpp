#include "queryEngine.h"
#include <iostream>

QueryEngine::QueryEngine() {
    wal.recover(*this);
    buildIndex();
}
void QueryEngine::buildIndex(){
    index.clear();
    for(int i = 0; i < bpm.getTotalPage(); i++){
        Page &p = bpm.getPage(i);
        vector<Record> rec =p.getRecords();
        for(auto &r : rec){
            index[r.key] = i;
        }
    }
}

void QueryEngine::insert(string key, string value){
    if(!recovering){
        wal.logInsert(key, value);
    }
    

    
    Record r{key,value}; 

    if(bpm.getTotalPage() == 0){
        Page newPage(0);
    
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
            Page newPage(bpm.getTotalPage());
            newPage.insert(r);
            bpm.cachePage(newPage);
            bpm.incrementTotalPages();           
        }
    }
    
    buildIndex();
}

string QueryEngine::search(const string &key){
    auto iter = index.find(key);
    if(iter == index.end()){
        return "NOT FOUND!";

    }
    int page_id = (*iter).second;
    Page &p = bpm.getPage(page_id);
    return p.search(key).second;
}

void QueryEngine::remove(const string &key){
    if(!recovering){
        wal.logRemove(key);
    }

    auto it = index.find(key);

    if(it == index.end()){
        return;
    }

    int page_id = it->second;

    Page &p = bpm.getPage(page_id);

    if(p.remove(key)){
        bpm.markDirty(page_id);
        index.erase(it);
    }
}

void QueryEngine::display() {
    for (int i = 0; i < bpm.getTotalPage(); i++) {
        Page &p = bpm.getPage(i);

        cout << "[Page " << p.getID() << "]\n";

        for (const auto &record : p.getRecords()) {
            cout << "  " << record.key
                 << " = " << record.value << "\n";
        }
    }
}

vector<Record> QueryEngine::prefixSearch(string prefix){
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

vector <Record> QueryEngine::rangeQuery(string st, string end){
    vector<Record> result;
    auto start = index.lower_bound(st);
    auto stop = index.upper_bound(end);

    for (auto it = start; it!=stop; it++){
        int page_id = (*it).second;
        Page &p = bpm.getPage(page_id);
        vector<Record>recs = p.getRecords();
        for (auto &r: recs){
            if(r.key == it->first){
                result.push_back(r);
            }
        }
    }
    return result;
}
 
