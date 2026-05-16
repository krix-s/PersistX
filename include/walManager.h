#ifndef WAL_MANAGER_H
#define WAL_MANAGER_H
#include <string>
using namespace std;
class WalManager{
    public:
    void logInsert(string key, string value);
    void logRemove(string key);
};

#endif



