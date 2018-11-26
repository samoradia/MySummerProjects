//Saagar Moradia
//9 August 2018
//CS106B
//Cache.cpp
//This file stores pages that have been recently accessed to allow them to be quickly accessed
//SOURCES USED FOR ALL 4 PARTS:
//Lecture slides 14-21
//Piazza
#define CacheCPP_Included
#include "Cache.h"
#include "hashmap.h"

template <typename ValueType>
Cache<ValueType>::Cache(int maxSize) {
   start = nullptr;
   end = nullptr;
   limit = maxSize;
   size = 0;
}

template <typename ValueType>
Cache<ValueType>::~Cache() {
    if (start != nullptr){
        while(start->next != nullptr){
            Node* hold = start;
            start = start->next;
            delete hold;
        }
        delete start;
    }
    maps.clear();
}

template <typename ValueType>
void Cache<ValueType>::put(const std::string& key, const ValueType& value) {
    if(start == nullptr){
        start = new Node{key, value, nullptr, nullptr};
        end = start;
        size++;
        maps.put(key,start);
    } else if (containsKey(key)){
        get(key);
    } else {
        //this case accounts for times when the list is not empty and the page is not already in the list
            Node* hold = new Node{key, value, nullptr, nullptr};
            hold->next = start;
            hold->prev = nullptr;
            start ->prev = hold;
            start= hold;
            maps.put(key,hold);
            if(size < limit){
                size++;
            } else {
                hold = end;
                end = hold->prev;
                maps.remove(hold->keys);
                delete hold;
                end->next = nullptr;

            }
    }
}

template <typename ValueType>
bool Cache<ValueType>::containsKey(const std::string& key) {
    if(maps.containsKey(key)){
        return true;
     }
    return false;
}

template <typename ValueType>
ValueType Cache<ValueType>::get(const std::string& key) {
   if(!containsKey(key)){
     error("Key not found");
   }     
    if (start!=nullptr){
        Node* hold = start;
        while(hold != nullptr){
            if(hold->keys == key){
                //if its the start- no need to change order
                if (hold == start){
                   // return start->values;
                }
                //check base case- no need to set the hold-> next if its end
                else if(hold  == end){
                    Node* curr = hold;
                    end  = curr->prev;
                    end->next = nullptr;
                    curr->next = start;
                    start->prev = curr;
                    start = curr;
                    curr->prev = nullptr;
                   // return curr->values;
                }
                //somewhere in the middle of the list, reorder
                else{
                Node* curr = hold;
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                start->prev = curr;
                curr->next = start;
                curr->prev = nullptr;
                start = curr;
                //return curr->values;
                }
            }
            hold = hold->next;
        }
    }
    return maps[key]->values;
}
