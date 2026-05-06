#ifndef STORAGE_H
#define STORAGE_H

#include <vector>
#include "diskManager.h"

class PageManager{
    private:
        vector<Page> pages;
        int NxtPageID = 0;
    public:
        void insert(string key, string value);
        string search(string key);
        void remove(string key);
        void display();
};
#endif