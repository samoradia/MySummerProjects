//Saagar Moradia
//9 August 2018
//CS106B
//Autocomplete.cpp
//This function implements functions and helper functions to allow the user to get a set of options of web pages to open based on what is inputted
#include "Autocomplete.h"
#include <cctype>
using namespace std;

Autocomplete::Autocomplete() { 
    TrieNode **arr = new TrieNode*[256]();
    root = new TrieNode{false, *arr};
}

Autocomplete::~Autocomplete() {
    TrieNode* hold = root;
    for(int i = 0; i<256; i++){
        while(hold->children[i] != nullptr)
            hold = hold->children[i];
    }
    delete hold;
}

void Autocomplete::add(const string& text) {
    TrieNode* hold = root;
    addHelper(hold, text);
}
void Autocomplete::addHelper(TrieNode* node, std::string key){

    if(key.length() == 0){
        //no more letters to add, mark it as a word
        node->isWord = true;
     } else {
        int index = (int)((unsigned char)key[0]);
        if(node->children[index] == nullptr){
            //make a new node since no node exists at this point
            TrieNode **arr = new TrieNode*[256]();
            node->children[index] = new TrieNode{false, *arr};
        }
            addHelper(node->children[index], key.substr(1));
    }
}

/* Find some recommendations! */
Set<string> Autocomplete::suggestionsFor(const string& prefix, int maxHits) const {
        TrieNode* hold = root;
        Set<string> suggest;
        //get the node that represents the prefix
        hold = isPrefix(hold,prefix);
        if(hold == nullptr){
            return suggest;
        }
        //change suggest to hold autocomplete options
        SearchHelper(hold, prefix, suggest, maxHits);
        return suggest;
}
Autocomplete::TrieNode* Autocomplete::isPrefix(TrieNode* curr, std::string prefix) const{
    if(prefix.length() ==0){
        return curr;
    }
    //continue to the next node, with the string becoming all characters after the first
    if(curr->children[(int)((unsigned char)prefix[0])] != nullptr){
        return isPrefix(curr->children[(int)((unsigned char)prefix[0])], prefix.substr(1));

    } else {
        //not found in trie
        return nullptr;
    }

}
void Autocomplete::SearchHelper(TrieNode* curr, std::string prefix, Set<std::string>& suggestions, int limit) const{
    if(suggestions.size() >= limit){
        //too many suggestions already
        return;
     } else {
        if(curr->isWord){
                //a valid autocorrect word
                suggestions.add(prefix);
        }
        char x;
        for(int i = 0; i <256; i++){
            x = (unsigned char)(i);
            if(curr->children[(unsigned char)i] != nullptr){
                prefix += x;
                SearchHelper(curr->children[i], prefix, suggestions, limit);
                prefix = prefix.substr(0,prefix.length()-1);
            }
        }

    }
}
