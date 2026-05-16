#ifndef QUERY_ENGINE_H
#define QUERY_ENGINE_H

#include "bufferPoolManager.h"
#include "walManager.h"
#include <iostream>
#include <map>
class queryEngine{
    private:
    BufferPoolManager bpm;
    map<string,int> index;
    WalManager wal;
    
    public:
    void buildIndex();
    void insert(string key, string value);
    string search(string key);
    void remove(string key);
    void display();
    vector<Record> prefixSearch(string prefix);
    vector<Record> rangeQuery(string st, string end);
    bool recovering = false;
};
#endif