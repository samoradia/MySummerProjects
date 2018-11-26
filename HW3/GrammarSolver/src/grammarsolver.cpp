//Saagar Moradia
//18 July 2018
//Grammar solver
//This program will take in a file of grammar rules and use it to recursively print out a number of phrases that can be built based on the
//rules
//sources:
//https://stanford.edu/~stepp/cppdoc/random.html
//Lecture slides 4,10
#include "grammarsolver.h"
#include "map.h"
#include "vector.h"
#include "strlib.h"
#include "random.h"
using namespace std;

void readFile(istream& input, Map <string, Vector<string> >& rules);
string generateResult(const Map <string, Vector<string> >& rules, string symbol, string& output);

/**
 * @brief grammarGenerate - Will generate a number of phrases or words based on inpouts from the user
 * @param input - the grammar file to create map from
 * @param symbol - the type of phrase or word to create
 * @param times - number of different iterations to do
 * @return
 */
Vector<string> grammarGenerate(istream& input, string symbol, int times) {
    if (symbol == ""){
        throw "Invalid symbol";
    }
    Map <string, Vector<string> >  rules;
    Vector<string> results;
    int count = 0;
    //create different phrases for the amount of times specified by user
    while(count < times){
        string output = "";
        readFile(input, rules);
        generateResult(rules, symbol, output);
        results.add(output);
        count++;
    }
    return results;
}
/**
 * @brief readFile Will read the grammar file and create a map of rules
 * @param input - file that contains grammar rules
 * @param rules - map that will contain the rules
 */
void readFile(istream& input, Map <string, Vector<string> >& rules){
    string line;
    while(getline(input, line)){
        string key;
        Vector <string> val;
        int count = 0;
        //check for seperation between key and value
        while (line.substr(count, 3) != "::="){
            key += line[count];
            count++;
        }
        if (rules.containsKey(key)){
            throw "Invalid file format";
        }
        //create the value, take off the key and seperator
        val = stringSplit(line.substr(count+3, line.length()-count-3), "|");
        rules.add(key, val);
    }
}
/**
 * @brief generateResult - This recursive method will take in the symbol given and look in the map created to recursively create the word type
 * @param rules - map of grammar rules
 * @param symbol - type of phrase to make
 * @param output - string to be added to vector
 * @return string that is created to hold the final type of speech
 */
string generateResult(const Map<string, Vector<string> >& rules, string symbol, string& output){
    //base case
    if (!rules.containsKey(symbol)){
        output += " " +trim(symbol);
        return " " + output;
        //recursive case
    } else {
        int word = randomInteger(0, rules[symbol].size()-1);
        symbol = rules[symbol][word];
        Vector <string> multkey = stringSplit(symbol, " ");
        //if a non-terminal key has more than one value associated with it, recursively call for each one
        for (int i = 0; i< multkey.size(); i++){
             generateResult(rules, multkey[i], output);
        }
        return output;
    }
}
