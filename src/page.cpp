#include "record.h"
#include "page.h"
#include <iostream>


bool Page::insert(Record r){

    if(current_size  + r.recSize() <= MAX_SIZE){
        records.push_back({r.key,r.value});
        current_size += r.recSize();
        return true;
    }
    else{
        return false;
    }
    
}

pair<bool,string> Page::search(string key){
    for (auto &r : records){
        if (r.key == key){
            return {true,r.value};
        }
    }
    return {false,""};
}

void Page::remove(string key){
    for (auto it = records.begin(); it != records.end();){
    
        if(it->key == key){
            for(auto &r : records){
                    current_size -= r.recSize();
                
            }
                        
            it = records.erase(it); //erase returns iterator of next element in vector
            
        }
        else{
            it++;
        }
    }
}

vector<Record> Page ::getRecords() const{
    vector<Record> r2;
    for(const auto &r: records){
        r2.push_back(r);
    }

    return r2;
}
//replacing display with get records just so that instead of printing records it makes records visible to storage for later displaying.


void Page:: setID(int id){
    ID = id;
}

int Page:: getID()const{ // here ID should be set only once by storage/page manager --- note to self: update to use constructer so that id is set on obj creation.
    return ID;
}
