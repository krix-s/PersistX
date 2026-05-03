#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "record.h"

class Storage{
    private:
        vector<Record> records;
    public:
        void insert(string key, string value);
        string search(string key);
        void remove(string key);
        void display();
};
#endif