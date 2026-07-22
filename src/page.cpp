#include "record.h"
#include "page.h"
#include <iostream>


bool Page::insert(const Record &r){

    if(current_size  + r.recSize() <= MAX_SIZE){
        records.push_back({r.key,r.value});
        current_size += r.recSize();
        return true;
    }
    else{
        return false;
    }
    
}

pair<bool,string> Page::search(const string& key){
    for (auto &r : records){
        if (r.key == key){
            return {true,r.value};
        }
    }
    return {false,""};
}

bool Page::remove(string& key){
    for (auto it = records.begin(); it != records.end();){
    
        if(it->key == key){
            current_size -= it->recSize();
                        
            it = records.erase(it);
            //erase returns iterator of next element in vector
            return true;
        }
        else{
            it++;
        }
    }
    return false;
}

const vector<Record> &Page ::getRecords() const{
    return this->records;
}



Page:: Page(int id){
    ID = id;
}

int Page:: getID()const{ 
    return ID;
}
