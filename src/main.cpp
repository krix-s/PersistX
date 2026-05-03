#include "storage.h"
#include <iostream>
using namespace std;

int main(){
    Storage db;

    db.insert("1", "tom");
    db.insert("2", "horse");
    db.insert("3","batman");
    db.insert("4", "blueberry");
    db.display();
    cout <<endl;
    cout << db.search("1");
    db.remove("1");
    cout << endl;
    cout << db.search("1");
    cout << endl;
    db.display();
    cout << endl;

    return 0;

}


