#ifndef RECORD_H
#define RECORD_H

#include <string>
using namespace std;
//class will be pvt by default
struct Record { 
    string key;
    string value;
 
    int recSize();
    
};

#endif