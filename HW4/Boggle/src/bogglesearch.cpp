//Saagar Moradia
//CS106B
//26 July 2018
//Boggle Search - This program will take in a grid that represents a boggle board and see if a user's input is valid,
//then search the grid for all remaining words
//Sources:
//Lecture slides 12, 13
#include <string>
#include "grid.h"
#include "lexicon.h"
#include "set.h"
#include "bogglegui.h"
#include "gwindow.h"

using namespace std;
//function prototypes
int getScore(string word);
void markSquare(GPoint square, Set<GPoint> &marked);
void unmarkSquare(GPoint square, Set<GPoint> &marked);
bool humanHelper(Grid<char>& board, string word, int score, Set<GPoint> &marked, GPoint pt);
void computerHelper(Grid<char> &board,
                    Lexicon &dictionary,
                    Set<string> &humanWords,
                    string word, Set<string> &compWords, GPoint pt, Set<GPoint> &marked);
/**
 * @brief humanWordSearch - will check if a user inputted word is valid for the given board
 * @param board- grid of chars that represents the board
 * @param dictionary - set of valid words
 * @param word - word to be searched
 * @return - bool if the word is valid
 */
bool humanWordSearch(Grid<char>& board, Lexicon& dictionary, string word) {
    BoggleGUI::clearHighlighting();
    if(!dictionary.contains(word)){
        return false;
    } else if (word.length() < BoggleGUI::MIN_WORD_LENGTH){
        return false;
    } else {
        int score = getScore(word);
        Set<GPoint> marked;
        //loop through the board of chars to find starting letter
        for(int r = 0; r < board.numRows(); r++){
            for(int c = 0; c<board.numCols();c++){
                GPoint pt1(r,c);
                BoggleGUI::setHighlighted(r,c,true);
                BoggleGUI::setAnimationDelay(100);
                //see if leading letter exists in the board
                if (word[0] == board[r][c]){
                    //only return if it is true, in case duplicate letters in board
                    if(humanHelper(board, word, score, marked, pt1)){ 
                        return true;
                    }
                }

                BoggleGUI::setHighlighted(r,c,false);
            }
        }
        return false;
    }
}
/**
 * @brief humanHelper This function will use recursive backtracking to check if an inputted word is possible to make on the board
 * @param board - grid of chars
 * @param word - word to be checked
 * @param score - score of word(only to be added if word is valid)
 * @param marked - a set of points that define spaces that have been checked
 * @param pt - point to be checked
 * @return - bool if the word is valid
 */
bool humanHelper(Grid<char>& board, string word, int score, Set<GPoint> &marked, GPoint pt){
    //base case
    if(word.length() == 0){
        BoggleGUI::scorePointsHuman(score);
        return true;
        //recursive case
    } else {
        if(board.inBounds(pt.getX(), pt.getY())&& !marked.contains(pt)){
            BoggleGUI::setHighlighted(pt.getX(), pt.getY(), true);
            BoggleGUI::setAnimationDelay(100);
            if(board[pt.getX()][pt.getY()] == word[0]){
                //recursively check the top and bottom three neighboring cells
                markSquare(pt, marked);
                for (int i = -1; i <2; i++){
                    GPoint pt1(pt.getX()-1, pt.getY()+i);
                    GPoint pt2(pt.getX()+1, pt.getY()+i);
                    //only return if true
                    if(humanHelper(board, word.substr(1), score, marked, pt1)){
                        return true;   
                    }
                    if(humanHelper(board, word.substr(1), score, marked, pt2)){
                        return true;
                    }
                }
                //recursively check the two neighboring cells(left and right)
                for (int i = -1; i <2; i+=2){
                    GPoint pt1(pt.getX(), pt.getY()+i);
                    //only return if true
                    if(humanHelper(board, word.substr(1), score, marked, pt1)){
                        return true;
                    }                  
                }
                BoggleGUI::setHighlighted(pt.getX(), pt.getY(), false);
                unmarkSquare(pt, marked);
            }
            BoggleGUI::setHighlighted(pt.getX(), pt.getY(), false);
        } 
        return false;
    }
}
/**
 * @brief computerWordSearch- This method will search the board for all remaining words not found by the user
 * @param board - grid of chars
 * @param dictionary - valid words to use
 * @param humanWords - words found by user
 * @return - set of all remaining words
 */
Set<string> computerWordSearch(Grid<char>& board, Lexicon& dictionary, Set<string>& humanWords) {
    string word = "";
    Set<string> compWords;
    Set<GPoint> marked;
    //find a starting letter
    for(int r = 0; r < board.numRows(); r++){
        for(int c = 0; c<board.numCols();c++){
            GPoint pt1(r,c);
            computerHelper(board, dictionary, humanWords, word, compWords, pt1, marked);
            word = "";
        }
    }

    return compWords;
}
/**
 * @brief computerHelper This function will recursively check the board for all words that exist in it
 * @param board - board of chars
 * @param dictionary - valid words that can be used
 * @param humanWords - words already selected by the user
 * @param word - word to be built into a valid word
 * @param compWords - set of words found by the program
 * @param pt - coordinates(row, col) of spot to be chosen
 * @param marked - points that have already been considered for the current call
 */
void computerHelper(Grid<char> &board,
                    Lexicon &dictionary,
                    Set<string> &humanWords,
                    string word, Set<string> &compWords, GPoint pt, Set<GPoint> &marked){
    //base case
    if(dictionary.contains(word) && word.length() >= BoggleGUI::MIN_WORD_LENGTH && !humanWords.contains(word) && !compWords.contains(word)){
        int score = getScore(word);
        cout << score << endl;
        BoggleGUI::scorePointsComputer(score);
        compWords.add(word);
    }else if(!dictionary.containsPrefix(word)){ //pruning recursive calls
        return;
        //recursive case
    } else {
        if(!marked.contains(pt) && board.inBounds(pt.getX(), pt.getY())){
            markSquare(pt, marked);
            //check the neighboring cells on top and bottom of the selected cell
            for (int i = -1; i <2; i++){
                word += board[pt.getX()][pt.getY()];
                GPoint pt1(pt.getX()-1, pt.getY()+i);
                GPoint pt2(pt.getX()+1, pt.getY()+i);
                computerHelper(board, dictionary, humanWords, word, compWords, pt1, marked);
                computerHelper(board, dictionary, humanWords, word, compWords, pt2, marked);
                word = word.substr(0,word.length()-1);
            }
            //recursively check the two neighboring cells(left and right)
            for (int i = -1; i <2; i+=2){
                word += board[pt.getX()][pt.getY()];
                GPoint pt1(pt.getX(), pt.getY()+i);
                computerHelper(board, dictionary, humanWords, word, compWords, pt1, marked);
                word = word.substr(0,word.length()-1);
            }
            unmarkSquare(pt,marked);
        }
    }
}
/**
 * @brief getScore This function will return the score of a word based on its length
 * @param word - word to be scored
 * @return - score of word
 */
int getScore(string word){
    if (word.length() <= 4 ){
        return 1;
    } else if(word.length() == 5){
        return 2;
    } else if(word.length() == 6){
        return 3;
    } else if(word.length() == 7){
        return 5;
    } else {
        return 11;
    }
}
/**
 * @brief markSquare This function will keep track of squares that have been considered by the algorithm by marking them
 * @param square - coordinates (row, col) of square to be marked
 * @param marked - set of marked squares
 */
void markSquare(GPoint square, Set<GPoint> &marked){
    marked.add(square);
}
/**
 * @brief unmarkSquare This function will remove a square from the marked set
 * @param square - coordinates (row, col) of square to be unmarked
 * @param marked - set of marked squares
 */
void unmarkSquare(GPoint square, Set<GPoint> &marked){
    marked.remove(square);
}
