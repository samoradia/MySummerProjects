//Saagar Moradia
//CS106B
//This program will take in a file of words and use it to construct a map of grams of length n, given by the user. This program
//will use the map to create text to mimic the style of writing used in the file, to a length decided by the user.
//Sources:
//Lecture slides 4,7
//https://stanford.edu/~stepp/cppdoc/Map-class.html
//https://stanford.edu/~stepp/cppdoc/random.html
//https://stanford.edu/~stepp/cppdoc/Queue-class.html

//packages
#include <iostream>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
#include <fstream>
#include "map.h"
#include "random.h"
#include "queue.h"
#include "error.h"

using namespace std;

//function prototypes
void intro();
int getFile(ifstream& infile);
void makeMap(ifstream& infile, Map<Queue <string>, Vector<string> >& gram, int numGrams);
void makeText(const Map<Queue <string>, Vector<string> >& gram, int numWords);
int getSentenceLength(int numWords);
void printQueue(Queue <string>& output);



int main() {
    intro();
    ifstream infile;
    Map <Queue <string>, Vector<string> > gram;
    int numGrams = getFile(infile);
    makeMap(infile, gram, numGrams);
    makeText(gram, numGrams);

    cout << "Exiting." << endl;
    return 0;
}
/**
 * @brief intro -  outputs a message to the user to introduce the program
 */
void intro(){
    cout << "Welcome to CS 106B/X Random Writer ('N-Grams')!" <<endl
         <<  "This program generates random text based on a document." <<endl
         <<  "Give me an input file and an 'N' value for groups" <<endl
         <<  "of words, and I'll create random text for you.\n" <<endl;
}

/**
 * @brief getFile - This function will ask the user for the name of the file to be mimiced and the N to be used in mimicing
 * @param infile - ifstream that runs through the file
 * @return int - numGram given by the user to be used in creating the map
 */
int getFile(ifstream& infile){
    int numGram = 0;
    promptUserForFile(infile, "Input File Name?");
    numGram = getInteger("Value of N?");
    if (numGram <2){
         numGram = getInteger("Invalid choice. N must be greater than or equal to 2. Try Again.");
    }

    return numGram-1;

}

/**
 * @brief makeMap - Will take an input file and create a map with keys of a vector length given my the user.
 * @param infile - ifstream that runs through the file inputted
 * @param gram - map to be created, will be changed
 * @param numGrams - number given to represent the length of the gram used
 * @param file - vector to be changed to hold the file
 */
void makeMap(ifstream &infile, Map<Queue<string>, Vector<string> > &gram, int numGrams){
    string word;
    Queue <string> key;
    Queue <string> hold;
    Vector <string> value;
    Vector <string> sizeFile;
    value.add("");
    //build the first key
    for (int i = 0; i< numGrams; i++){
        infile>> word;
        key.enqueue(word);
        hold.enqueue(word);
    }
    //use the first key to create the rest of the keys and values
    while (infile >> word){
        value.remove(0);
        value.add(word);
        sizeFile.add(word);
        if(gram.containsKey(key)){
            gram[key].add(value[0]);
        } else {
            gram.put(key,value);
        }
        key.dequeue();
        key.enqueue(word);
    }
    //crash program if N ends up being greater than size of file
    if (numGrams > sizeFile.size()){
        error("N cannot be greater than the number of words in the file");
    }
    //loop the map from the end to the beginning
    for(int i = 0; i <numGrams; i++){
        value.remove(0);
        value.add(hold.dequeue());
        if(gram.containsKey(key)){
            gram[key].add(value[0]);
        } else {
            gram.put(key,value);
        }
        key.enqueue(value[0]);
        key.dequeue();
    }
    infile.close();
}

/**
 * @brief getSentenceLength - Will prompt the user to enter a number of words to randomly generate
 * @return int - number of words to start
 */
int getSentenceLength(int numWords){

    int len = getInteger("# of random words to generate (0 to exit)");
    while (len < numWords && len != 0){
        len = getInteger("Invalid response. Must be greater than N(0 to exit)");
    }
    return len;
}
/**
 * @brief printQueue - Prints out the queue in the format needed for the final output
 * @param output - queue to be printed
 */
void printQueue(Queue<string> &output){
    cout << "... ";
    while (!output.isEmpty()){
        cout << output.dequeue() << " ";
    }
    cout << " ..." << endl;
}

/**
 * @brief makeText - This function ask the user for the number of words to create then user the map created from the input file to generate that many
 *        words in the style of that file
 * @param gram - The map created to mimic the style of the input file
 * @param numWords - the N used for the Ngram
 * @param file - the vector that holds the original file, to be used to choose a random start
 * @return
 */
void makeText(const Map<Queue<string>, Vector<string> > &gram, int numWords){
   Queue <string> output;
   Queue <string> key;
   Vector <string> holder;
   Vector <Queue<string> > mapKeys;
   string word;
   int len = getSentenceLength(numWords);
   int count = numWords;
   while(len > 0){
       //choose random starting place by randomly choosing key
       mapKeys = gram.keys();
       key = mapKeys[randomInteger(0, mapKeys.size()-1)];
       while (count < len){
           holder = gram[key];
           word = holder[randomInteger(0,gram[key].size()-1)];
           output.enqueue(key.dequeue());
           key.enqueue(word);
           count++;
       }
       //add the last numWords words into the queue
       for(int i = 0; i< numWords; i++){
           output.enqueue(key.dequeue());
       }
       printQueue(output);
       len = getSentenceLength(numWords);
       count = numWords;
   }
}

