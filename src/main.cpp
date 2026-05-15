#include <iostream>
#include "queryEngine.h"

using namespace std;

int main() {
    queryEngine db;

    // Insertin enough records to force multiple pages
    for (int i = 0; i < 100; i++) {
        string key = to_string(i);
        string value(100, 'a' + (i % 26));  // 100-char string

        db.insert(key, value);
    }


    
    db.display();

    
    cout << "Search 10: " << db.search("10") << endl;
    cout << "Search 999: " << db.search("999") << endl;

    
    db.remove("10");
    
    cout << "Search 10: " << db.search("10") << endl;

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

    db.insert("apple", "fruit");
    db.insert("apricot", "fruit");

    auto results = db.prefixSearch("ap");
    for (const auto &r : results) {
        cout << "(key:" << r.key << " value:" << r.value << ")" << endl;
    }

    return 0;





}


