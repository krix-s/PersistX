#ifndef PAGE_H
#define PAGE_H

#include "record.h"
#include <vector>
#include <string>
#include <utility>

using namespace std;

class Page{
    private:
        vector<Record> records;
        int current_size = 0;
        static const int MAX_SIZE = 4096;

    public:
        bool insert(Record r);
        pair<bool,string> search(string key);
        void remove(string key);
        vector<Record> getRecords();
};

#endif