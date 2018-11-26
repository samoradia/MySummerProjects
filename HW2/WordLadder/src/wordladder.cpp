//Saagar Moradia
//CS106B
//This program will take in a file to act as a dictionary and ask the user for two equal length words.
//It will then find the shortest possible word ladder between the two words, if possible.
//Sources:
//https://stanford.edu/~stepp/cppdoc/Set-class.html
// Lecture slides 4,7
//http://www.cplusplus.com/forum/beginner/25649/


#include <iostream>
#include "console.h"
#include "set.h"
#include "queue.h"
#include "stack.h"
#include <fstream>
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"

using namespace std;
//function prototypes
void intro();
void createDict(Set<string>& dictionary);
void promptUser(string &word1, string &word2, Set<string> &dictionary);
bool checkInput(string &word1, string &word2, Set<string> &dictionary, string &error);
Stack <string> makeLadder(const Set<string> &dict, const string &word1, const string &word2, Queue <Stack<string> > &ladder);
string retLadder(Stack<string> &hold, Queue <Stack<string> > &ladder);

int main() {//implement enter to exit, loop after completed once
    string word1 = "";
    string word2 = "";
    Set<string> dictionary;
    Queue <Stack<string> > ladder;
    Stack<string> holders;
    createDict(dictionary);
    promptUser(word1, word2, dictionary);
    while (!word1.empty() || !word2.empty()){
        //will store the appropriate output from the ladder created in to a string variable
        holders = makeLadder(dictionary, word1, word2, ladder);
        string finalLadder = retLadder(holders,ladder);
        cout << finalLadder << endl;
        promptUser(word1, word2, dictionary);
    }
    cout << "Exiting." << endl;
    return 0;
}
/**
 * @brief intro - This function displays a welcome message to the user to explain the program
 */
void intro(){
   cout << "Welcome to CS 106B/X Word Ladder!" <<endl
        << "Please give me two English words, and I will convert the" << endl
        << "first into the second by modifying one letter at a time." << endl;
}
/**
 * @brief createDict - This function will prompt the user for the name of a file to act as the dictionary
 * @param dictionary - hold the words to be checked when the ladder is being found
 */
void createDict(Set<string>& dictionary){
    ifstream infile;
    promptUserForFile(infile, "Dictionary File Name?: ");
    string word;
    while(getline(infile, word)){
        dictionary.add(word);
    }
}
/**
 * @brief promptUser - prompts the user for the two words to form the ladder, and checks for invalid inputs
 * @param word1 - first word to form ladder
 * @param word2 - second word to form ladder
 * @param dictionary - set of valid words
 */
void promptUser(string &word1, string &word2, Set<string>& dictionary){
    string error = "";
    word1 = getLine("Enter word 1");
    word2 = getLine("Enter word 2");
    if (word1.empty() || word2.empty()){
    } else {
        while (!checkInput(word1, word2, dictionary, error)){
            cout << error << endl;
            word1 = getLine("Enter word 1");
            word2 = getLine("Enter word 2");
        }
    }
}
/**
 * @brief checkInput - checks if the inputs are valid
 * @param word1 - first word to form ladder
 * @param word2 - second word to form ladder
 * @param dictionary - set of valid words
 * @param error - error message, if needed
 * @return - if input is valid or not
 */
bool checkInput(string &word1, string &word2, Set<string> &dictionary, string &error){
    //convert both words to lower
    for (int i =0; i< word1.length(); i++){
       word1[i] =  tolower(word1[i]);
       word2[i] = tolower(word2[i]);
    }
    if(word1.length() != word2.length()){
        error = "The words must be the same length";
        return false;
    } else if (word1 == word2) {
        error = "The words must be different";
        return false;
    } else if (!dictionary.contains(word1) || !dictionary.contains(word2)) {
        error = "The words must be in the dictionary";
        return false;
    } else {
        return true;
    }
}
/**
 * @brief makeLadder - This function will create the word ladder from the second word to the first word, if possible
 * @param dict - Set representing the valid words that can be used
 * @param word1 - initial word
 * @param word2 - ending word
 * @return - stack of the ladder
 */
Stack <string> makeLadder(const Set<string> &dict, const string &word1, const string &word2, Queue <Stack<string> > &ladder){
    Stack<string> holder;
    Set <string> used;
    holder.push(word1);
    ladder.enqueue(holder);
    string check = word1;
    string confCheck = "";
    used.add(word1);
    while (!ladder.isEmpty() && confCheck != word2){
        holder = ladder.dequeue();
        for (int i = 0; i< check.length(); i++){
            check = holder.peek();
            for (int j = 0; j < 26; j++){
                check[i] = 'a'+ j;
                if (check == word2){
                    confCheck = word2;
                }
                if (dict.contains(check) && confCheck != word2 && !used.contains(check)){
                    holder.push(check);
                    ladder.enqueue(holder);
                    holder.pop();
                    used.add(check);
                }
            }
        }
    }
    holder.push(confCheck);
    used.clear();

    return holder;
}
/**
 * @brief retLadder - This function will create a string to be outputted based on the stack given
 * @param hold - Represents the ladder created
 * @return  - string that represents the output
 */
string retLadder(Stack<string> &hold, Queue <Stack<string> > &ladder){
    string output = "";
    if (ladder.isEmpty()){
        return "No valid Word Ladder was found.";
    }
    while (!hold.isEmpty()){
        output += hold.pop() + " ";
    }
    hold.clear();
    ladder.clear();
    return output;
}
