#include "bufferPoolManager.h"
#include <iostream>
using namespace std;
//unorderd map answeres where is page x
//heap answers which page is oldest


void BufferPoolManager::evictPage(){
    while(!minHeap.empty()){
        auto oldest = minHeap.top();
        minHeap.pop();
        int ts = oldest.first;
        int id = oldest.second;
        auto it = bufferPool.find(id);
        if(it == bufferPool.end()){
            continue; //the page doesnt exist (alr evicted)
        }
        if(ts != it->second.timestamp){
            //Ignore stale heap entries. Page was accessed again
            continue; 
        }

        if(it->second.dirty){
            //dirty pages must be flushed before eviction
            dm.writePage(it->second.page);
           
        }
        bufferPool.erase(id);
        return;
    }
}

Page& BufferPoolManager::getPage(int page_id){
    auto it = bufferPool.find(page_id);
    
    if(it != bufferPool.end()){
        currentTime++;
        it->second.timestamp = currentTime;
        minHeap.push({currentTime,page_id});
        return it->second.page;
    }
    
    if(bufferPool.size() >=MAX_BUFFER_SIZE){
        evictPage();
    }
    auto result = dm.readPage(page_id);
    currentTime++;
    BufferFrame frame(result.second, currentTime, false);
    bufferPool.insert({page_id,frame});
    minHeap.push({currentTime, page_id});
    return bufferPool.find(page_id)->second.page;
}

/*logic for eviction
suppose page 1 accessed at time 5
heap(5,1)
then again accessed at time 20
heap(20,1)
must evict (5,1)*/

int BufferPoolManager::getTotalPage(){
    return totalPages;
}
void BufferPoolManager::markDirty(int page_id){
    auto it = bufferPool.find(page_id);
    if(it != bufferPool.end()){
        it->second.dirty = true;
    }
}
void BufferPoolManager::cachePage(const Page& page){
    if(bufferPool.size() >= MAX_BUFFER_SIZE){
        evictPage();
    }
    currentTime++;
    BufferFrame frame(page,currentTime,true);

    //use insert() instead of operator[] because BufferFrame has
    //no default constructor. Operator [] would try to
    //default construct a BufferFrame when key is absent bufferframe

    bufferPool.insert({page.getID(),frame});
    minHeap.push({currentTime, page.getID()});
}

void BufferPoolManager ::incrementTotalPages(){
    totalPages++;
}

