#include "storage.h"
#include <iostream>
using namespace std;
//all functions must be of the specific class in header file hence ::
void Storage::insert(string key, string value){
    records.push_back({key,value});
}

string Storage::search(string key){
    for (auto &r : records){
        if (r.key == key){
            return r.value;
        }
    }
    return "NOT FOUND";
}
//erase invalides iterator hence range based loop doesnt work.
void Storage::remove(string key){
    for (auto it = records.begin(); it != records.end();){
    
        if(it->key == key){
            it = records.erase(it); //erase returns iterator of next element in vector.
        }
        else{
            it++;
        }
    }
}

void Storage:: display(){
    for (const auto &r : records){
        cout << r.key <<":"<< r.value << " ";
    }
}
