#ifndef QUERY_ENGINE_H
#define QUERY_ENGINE_H

#include "bufferPoolManager.h"
#include "walManager.h"
#include <iostream>
#include <map>
class QueryEngine{
    private:
    BufferPoolManager bpm;
    map<string,int> index;
    WalManager wal;
    void buildIndex();
    public:
    QueryEngine();
  
    void insert(string key, string value);
    string search(const string& key);
    void remove(const string &key);
    void display();
    vector<Record> prefixSearch(string prefix);
    vector<Record> rangeQuery(string st, string end);
    bool recovering = false;
};
#endif