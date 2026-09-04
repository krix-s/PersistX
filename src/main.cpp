#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include "queryEngine.h"

using namespace std;

int main() {
    QueryEngine db;

    cout << "=========================\n";
    cout << "        PersistX\n";
    cout << "=========================\n";
    cout << "Type HELP for commands.\n\n";

    string line;

    while (true) {
        cout << "PersistX> ";
        getline(cin, line);

        if (line.empty()) {
            continue;
        }

        stringstream ss(line);
        string command;
        ss >> command;

        if (command == "INSERT") {
            string key, value;
            ss >> key >> value;

            if (key.empty() || value.empty()) {
                cout << "Usage: INSERT <key> <value>\n";
                continue;
            }

            db.insert(key, value);
            cout << "OK\n";
        }

        else if (command == "GET") {
            string key;
            ss >> key;

            if (key.empty()) {
                cout << "Usage: GET <key>\n";
                continue;
            }

            cout << db.search(key) << "\n";
        }

        else if (command == "DELETE") {
            string key;
            ss >> key;

            if (key.empty()) {
                cout << "Usage: DELETE <key>\n";
                continue;
            }

            db.remove(key);
            cout << "OK\n";
        }

        else if (command == "PREFIX") {
            string prefix;
            ss >> prefix;

            if (prefix.empty()) {
                cout << "Usage: PREFIX <prefix>\n";
                continue;
            }

            auto results = db.prefixSearch(prefix);

            for (const auto &r : results) {
                cout << r.key << " = " << r.value << "\n";
            }

            cout << "Found " << results.size() << " record(s).\n";
        }

        else if (command == "RANGE") {
            string start, end;
            ss >> start >> end;

            if (start.empty() || end.empty()) {
                cout << "Usage: RANGE <start> <end>\n";
                continue;
            }

            auto results = db.rangeQuery(start, end);

            for (const auto &r : results) {
                cout << r.key << " = " << r.value << "\n";
            }

            cout << "Found " << results.size() << " record(s).\n";
        }

        else if (command == "DISPLAY") {
            db.display();
        }

        else if (command == "HELP") {
            cout << "\n";
            cout << "INSERT <key> <value>\n";
            cout << "GET <key>\n";
            cout << "DELETE <key>\n";
            cout << "PREFIX <prefix>\n";
            cout << "RANGE <start> <end>\n";
            cout << "DISPLAY\n";
            cout << "CRASH\n";
            cout << "EXIT\n\n";
        }

        else if (command == "CRASH") {
            cout << "Simulating crash...\n";
            abort();
        }

        else if (command == "EXIT") {
            cout << "Shutting down PersistX.\n";
            break;
        }

        else {
            cout << "Unknown command. Type HELP.\n";
        }
    }

    return 0;
}