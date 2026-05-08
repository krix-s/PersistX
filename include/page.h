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
        int ID;

    public:
        bool insert(Record r);
        pair<bool,string> search(string key);
        bool remove(string key);
        vector<Record> getRecords() const;
        void setID(int id);
        int getID() const;
};

#endif