//Saagar Moradia
//9 August 2018
//CS106B
//History .ccp file
//This file instatiates the methods outlined in the .h file, to allow the user to use the forward and back buttons in the browser
//sources:
//Lecture slides 14,15,16,17,18,19
#include "History.h"
#include "error.h"
using namespace std;

History::History() {
    start = nullptr;
    end = nullptr;
    curr = start;
}

History::~History() {
    if (start != nullptr){
        while(start->next != nullptr){
            Node* hold = start;
            start = start->next;
            delete hold;
        }
    }
}

bool History::hasNext() const {
    if(curr != nullptr){
        if(curr->next !=nullptr){
            return true;
        } else {
            return false;
        }
    } else {
        return false;         
    }
}

bool History::hasPrevious() const {
    if(curr != nullptr){
        if(curr->prev !=nullptr){
            return true;
        } else {
            return false;
        }
    } else {
           return false;
        }
}

string History::next() {
    if(!hasNext()){
        error("There is no next page");
    } else {
        curr = curr->next;

    }
    return curr->title;
}

string History::previous() {
    if(!hasPrevious()){
        error("There is no previous page");
    } else {
        curr = curr->prev;

    }
    return curr->title;
}

void History::goTo(const string& page) {
    if(curr == nullptr){
        Node* hold = new Node{page, nullptr, end};
        start = hold;
        curr =hold;
        end = hold;
    } else {
        //delete any pages in the linked list after the current page
        Node* hold = curr;
        while (hold->next != nullptr){
            Node* hold2 = hold->next;
            hold = hold2->next;
            delete hold2;
        }
        //add new page to list and change curr pointer accordingly
        curr->next = new Node{page, curr, nullptr};
        curr = curr ->next;
        curr->next = nullptr;
        end = curr;
    }

}
