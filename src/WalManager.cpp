#include "walManager.h"
#include <fstream>

void WalManager ::logInsert(string key, string value){
    ofstream fout("data/wal.log",ios::app);
    fout << "INSERT|" << key << "|" << value << endl;
    fout.close();
}

void WalManager :: logRemove(string key){
    ofstream fout ("data/wal.log", ios::app);
    fout << "REMOVE|" << key << endl;
    fout.close();
}
