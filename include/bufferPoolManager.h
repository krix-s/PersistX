#include "page.h"
#include "diskManager.h"
#include <unordered_map>
#include <queue>
#include <utility>
#include <vector>
#include <functional>
#include <string>



using namespace std;

struct BufferFrame{
    //to contain metadata
    Page page;
    int timestamp;   
    bool dirty;

    BufferFrame(const Page& p,int ts, bool d)
        :page(p), timestamp(ts), dirty(d)
    {}
    //members are constructed before the constructor body runs
    //Since Page has no default constructor, we initialize it directly here
    //using member initializer lists

};

class BufferPoolManager{
    private:
    unordered_map<int, BufferFrame> bufferPool;
    priority_queue <
        pair<int,int>,
        vector<pair<int,int>>,
        greater<pair<int,int>>
    > minHeap;
    
    int MAX_BUFFER_SIZE = 3;
    int currentTime = 0;
    int totalPages = 0;
    DiskManager dm;
    void evictPage();
    public:
    Page& getPage(int page_id);
    int getTotalPage();
    void markDirty(int page_id);
    void cachePage(const Page& page);
    void incrementTotalPages();

};

