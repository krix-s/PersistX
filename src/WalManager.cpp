#include "walManager.h"
#include "queryEngine.h"
#include <fstream>
#include <sstream>
#include <string>
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

void WalManager:: recover(queryEngine &db){
    ifstream f("data/wal.log");
    if(!f.is_open()){
        return;
    }
    db.recovering = true;

    string line;
    while(getline(f,line)){
        stringstream ss(line);

        string op;
        string key;
        string val;

        getline(ss,op,'|');
        getline(ss,key,'|');

        if(op == "INSERT"){
            getline(ss,val);
            db.insert(key,val);
        }
        else if(op == "REMOVE"){
            db.remove(key);
        }
    }
    db.recovering == false;
    f.close();
    ofstream clearfile("data/wal.log", ios::trunc);
    clearfile.close();
}
