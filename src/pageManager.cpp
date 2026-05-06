#include "pageManager.h"
#include "page.h"
#include <iostream>
using namespace std;
//all functions must be of the specific class in header file hence ::
void PageManager::insert(string key, string value){

    DiskManager dm;
    Record r{key,value}; //instead of page, storage creates record and passes it down to page to insert
    if(pages.empty()){
        Page newPage;
        
        newPage.setID(NxtPageID);
        NxtPageID ++;
        newPage.insert(r);
        pages.push_back(newPage);
        dm.writePage(newPage);
    }
    else{
        Page &p = pages.back();
        if(!p.insert(r)){
            
            Page newPage;
            newPage.setID(NxtPageID);
            NxtPageID ++;
            newPage.insert(r);
            pages.push_back(newPage);
            dm.writePage(newPage);
        }
        else{
            dm.writePage(p);
        }
    }

        
}
   


string PageManager::search(string key){
    for(auto &p : pages){
        auto result = p.search(key);
        if (result.first){
            return result.second;
        }
        
    }
    return "NOT FOUND";
}

//erase invalides iterator hence range based loop doesnt work.
void PageManager::remove(string key){
    for(auto &p : pages){
        p.remove(key);
        break;
    }
}

void PageManager:: display(){
    for (auto &p : pages){
        for( auto &d : p.getRecords()){
            cout << p.getID() << endl;  //comment this line later - only for testing pageManager.
            cout << "(key:" << d.key << " value:" << d.value << ")";  
        }
    }
}
