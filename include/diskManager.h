#include "page.h"
#include <fstream>
#include <string>

class DiskManager{
    private:
    string filename;
    public:
    bool writePage(const Page &p);
    pair<bool,Page> readPage(int page_id);

};