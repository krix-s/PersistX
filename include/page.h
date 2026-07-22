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
        bool insert(const Record &r);
        pair<bool,string> search(const string &key);
        bool remove(string &key);
        const vector<Record> &getRecords() const;
        Page(int id);
        int getID() const;
};

#endif