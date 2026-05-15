#ifndef QUERY_ENGINE_H
#define QUERY_ENGINE_H

#include "bufferPoolManager.h"
#include <iostream>
class queryEngine{
    private:
    BufferPoolManager bpm;
    
    public:
    void insert(string key, string value);
    string search(string key);
    void remove(string key);
    void display();
    vector<Record> prefixSearch(string prefix);
};
#endif