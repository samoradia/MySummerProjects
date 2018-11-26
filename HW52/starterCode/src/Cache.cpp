//Saagar Moradia
//9 August 2018
//CS106B
//Cache.cpp
//This file stores pages that have been recently accessed to allow them to be quickly accessed
#define CacheCPP_Included
#include "Cache.h"

template <typename ValueType>
Cache<ValueType>::Cache(int maxSize) {
   start = nullptr;
   end = nullptr;
   limit = maxSize;
}

template <typename ValueType>
Cache<ValueType>::~Cache() {
    if (start != nullptr){
        while(start->next != nullptr){
            Node* hold = start;
            start = start->next;
            delete hold;
        }
    }
}

template <typename ValueType>
void Cache<ValueType>::put(const std::string& key, const ValueType& value) {
    if(start == nullptr){
        start = new Node{key, value, nullptr, nullptr};
        end = start;

    } else if (containsKey(key)){//change from O(n)
        //change the order of the page being loaded
        Node* hold = start;
        while(hold->next != nullptr){
            if(hold->key == key){
                Node* curr = hold;
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                start->prev = curr;
                curr->next = start;
                curr->prev = nullptr;
                start = curr;
            }
            hold = hold->next;
        }
    } else {
        //this case accounts for times when the list is not empty and the page is not already in the list
        Node* hold = new Node{key, value, start, nullptr};
        start = hold;
    }
}

template <typename ValueType>
bool Cache<ValueType>::containsKey(const std::string& key) {
    if(start!=nullptr){
        Node* hold = start;
        while(hold->next !=nullptr){
            if(hold->key == key){
                return true;
            }
            hold = hold->next;
        }
    }
    return false;
}

template <typename ValueType>
ValueType Cache<ValueType>::get(const std::string& key) {
    if (!containsKey(key)){
         error("Key not found");
    }
    if (start!=nullptr){
        Node* hold = start;
        while(hold->next != nullptr){
            if(hold->key == key){
                Node* curr = hold;
                curr->prev->next = curr->next;
                curr->next->prev = curr->prev;
                start->prev = curr;
                curr->next = start;
                curr->prev = nullptr;
                start = curr;
            }
            hold = hold->next;
    }

    return start->value;
}
