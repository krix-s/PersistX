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
        if(ts != it->second.timestamp){//if page still exists after heap popping
            continue; // stale page;    (newer access exists)
        }

        if(it->second.dirty){//but if the page is dirty, then we must write to os and ONLY then erase from bufferpool or else we will loose that data forever
            dm.writePage(it->second.page);
            return;
        }
        bufferPool.erase(id);
    }

}

Page& BufferPoolManager::getPage(int page_id){
    auto it = bufferPool.find(page_id);
    
    if(it != bufferPool.end()){//cache 
        currentTime++;
        it->second.timestamp = currentTime;
        minHeap.push({currentTime,page_id});
        return it->second.page;
    }
    //cache miss
    if(bufferPool.size() >=MAX_BUFFER_SIZE){
        //cache full
        evictPage();
    }
    auto result = dm.readPage(page_id);
    
    /*if(result.first == false){
        return result.second;
    }*/
    BufferFrame frame;
    frame.page = result.second;
    frame.dirty = false;
    currentTime++;
    frame.timestamp = currentTime;
    bufferPool[page_id] = frame;
    minHeap.push({currentTime, page_id});
    return bufferPool[page_id].page;


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
void BufferPoolManager::cachePage(Page page){
    if(bufferPool.size() >= MAX_BUFFER_SIZE){
        evictPage();
    }
    BufferFrame frame;
    frame.page = page;
    frame.dirty = false;
    currentTime++;
    frame.timestamp = currentTime;
    bufferPool[page.getID()] = frame;
    minHeap.push({currentTime, page.getID()});
}

void BufferPoolManager ::incrementTotalPages(){
    totalPages++;
}

