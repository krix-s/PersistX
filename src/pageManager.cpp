#include "pageManager.h"
#include "page.h"
#include <iostream>
using namespace std;
//all functions must be of the specific class in header file hence ::
void Storage::insert(string key, string value){
    Record r{key,value}; //instead of page, storage creates record and passes it down to page to insert
    if(pages.empty()){
        Page newPage;
        
        newPage.setID(NxtPageID);
        NxtPageID ++;
        newPage.insert(r);
        pages.push_back(newPage);
    }
    else{
        if(!pages.back().insert(r)){
            Page newPage;
            newPage.setID(NxtPageID);
            NxtPageID +=1;
            newPage.insert(r);
            pages.push_back(newPage); 
        }
    }

        
}
   


string Storage::search(string key){
    for(auto &p : pages){
        auto result = p.search(key);
        if (result.first){
            return result.second;
        }
        
    }
    return "NOT FOUND";
}

//erase invalides iterator hence range based loop doesnt work.
void Storage::remove(string key){
    for(auto &p : pages){
        p.remove(key);
        break;
    }
}

void Storage:: display(){
    for (auto &p : pages){
        for( auto &d : p.getRecords()){
            cout << p.getID() << endl;  //comment this line later - only for testing pageManager.
            cout << "(key:" << d.key << " value:" << d.value << ")";  
        }
    }
}
