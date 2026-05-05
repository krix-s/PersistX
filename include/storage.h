#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "page.h"

class Storage{
    private:
        vector<Page> pages;
    public:
        void insert(string key, string value);
        string search(string key);
        void remove(string key);
        void display();
};
#endif