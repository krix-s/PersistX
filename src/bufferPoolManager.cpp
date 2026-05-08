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




void BufferPoolManager::insert(string key, string value){

    
    Record r{key,value}; 

    if(totalPages == 0){
        Page newPage;
    
        newPage.setID(0);
    
        newPage.insert(r);
        BufferFrame frame;
        frame.page = newPage;
        currentTime++;
        frame.timestamp = currentTime;
        frame.dirty = true;
        bufferPool[0] = frame;
        minHeap.push({currentTime,0});
        totalPages++ ;  
    }
    else{//totalpages-1 = lastpage id
        Page &p = getPage(totalPages-1);
        if(p.insert(r)){
            bufferPool[totalPages-1].dirty = true;
        }
        else{
            //new pageid == total pages
            Page newPage;
            newPage.setID(totalPages);
            newPage.insert(r);
            BufferFrame frame;
            frame.page = newPage;
            currentTime++;
            frame.timestamp = currentTime;
            frame.dirty = true;
            bufferPool[totalPages] = frame;
            minHeap.push({currentTime,totalPages});
            totalPages++ ;            
        }
    }
    
    
}

string BufferPoolManager::search(string key){
    for(int i = 0; i < totalPages; i++){
        Page &p = getPage(i);
        auto result = p.search(key);

        if (result.first){
            return result.second;
        }
        
    }
    return "NOT FOUND";
}

//erase invalides iterator hence range based loop doesnt work.
void BufferPoolManager::remove(string key){
    for(int i = 0; i < totalPages; i++){
        Page &p = getPage(i);
        if(p.remove(key)){
            bufferPool[i].dirty = true;
            return;
        }
    }
}

void BufferPoolManager:: display(){
    for(int i = 0; i < totalPages; i++){
        Page &p = getPage(i);
        for( auto &d : p.getRecords()){
            cout << p.getID() << endl;  //comment this line later - only for testing pageManager.
            cout << "(key:" << d.key << " value:" << d.value << ")";  
        }
    }
}