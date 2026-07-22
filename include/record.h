#ifndef RECORD_H
#define RECORD_H

#include <string>
using namespace std;
struct Record { 
    string key;
    string value;
 
    int recSize() const;
    
};

#endif