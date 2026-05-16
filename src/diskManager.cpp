#include "diskManager.h"
//#include "iostream"
bool DiskManager::writePage(const Page &p){
    //cout << "writing page";
    string filename = "data/page_" + to_string(p.getID()) + ".txt";
    ofstream file (filename);
    if(!file){
        return false;
    }
    
    for(auto &r : p.getRecords()){
        file << r.key << "|" << r.value << endl;
    }
    return true;

}

pair<bool,Page> DiskManager::readPage(int page_id){
    string filename = "data/page_" + to_string(page_id) + ".txt";
    ifstream file (filename);
    if(!file){
        Page p; //empty page for returning if file missing
        p.setID(page_id);
        return{false,p};
    }
    Page p;
    p.setID(page_id);
    string line;
    while(getline(file,line)){
        int delimiterPosition = line.find("|");
        string key = line.substr(0,delimiterPosition);
        string value = line.substr(delimiterPosition+1);
        Record r{key,value};
        p.insert(r);
    }
    return {true,p};
}

