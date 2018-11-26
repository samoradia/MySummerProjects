// Saagar Moradia
//CS 106B
//Game of Life Program
/*This program reads a file that contains information to set up a grid
 * for the game of life. The user will then be able to run through generations
 * of the game using different commands, with the game abiding by specific rules.
 * The game's progress will output in a GUI that will update as the game progresses.
 */
/* Citations:
 * lecture slides 3,4 (Grids and File i/o)
 * c++.com - istream.get(), stoi()
 *https://stackoverflow.com/questions/5966698/error-use-of-deleted-function
 *
 */

#include <iostream>
#include "console.h"
#include "filelib.h"
#include "simpio.h"
#include "strlib.h"
#include "lifegui.h"
#include <fstream>

using namespace std;

//Function Prototypes
void animate(int num, Grid<bool> &gameOfLife);
Grid<bool> tick(Grid <bool> &gameOfLife);
Grid<bool> openFile();
void prompt( Grid <bool> &gameOfLife);
void intro();
void makeGrid(ifstream &infile, Grid<bool> &game);
bool checkState(int row, int col, Grid <bool>& game);
void takeAction(int count, Grid <bool> &gameOfLife, Grid <bool>& newGame, int row, int col);
void repeat();
void printGrid(Grid <bool> &newGame);

int main() {
    intro();
    LifeGUI::initialize();
    Grid <bool> gameOfLife = openFile();
    prompt(gameOfLife);
    cout << "Have a nice Life!" << endl;
    return 0;
}
/**
 * @brief intro This function displays a message to the user at the beginning of
 * the program, outlining the game and its rules.
 */
void intro(){
    cout << "Welcome to the CS 106B/X Game of Life!" << endl
         << "This program simulates the lifecycle of a bacterial colony." << endl
         << "Cells (X) live and die by the following rules:" << endl
         << "* A cell with 1 or fewer neighbors dies." << endl
         << "* Locations with 2 neighbors remain stable." << endl
         << "* Locations with 3 neighbors will create life." << endl
         << "* A cell with 4 or more neighbors dies." << "\n" << endl;
}
/**
 * @brief Helper function to openFile(), takes the input from the file and turns it into a Grid
 * @param infile file to be read
 * @param game grid that represents the colony
 */
void makeGrid(ifstream &infile, Grid<bool> &game){
    int row = 0;
    int col = 0;
    string line;

    //find number of rows in file
    getline(infile, line); //infile >> row
    row = stoi(line);

    //find number of columns in file using same logic as for rows
    getline(infile, line);
    col = stoi(line);

    game.resize(row,col);
    LifeGUI::resize(row,col);
    //the file will always have 2 more rows than the number of rows in the grid
    //all other info is irrelevant to the program and will be ignored, it will stop after the number of rows
    for(int i=0;i<row;i++){
        getline(infile, line);
        for(int j = 0; j < col;j++){
            if(line[j] == 'X'){
                game[i][j] = true;
                LifeGUI::fillCell(i,j);
            }
            else{
                game[i][j] = false;
            }
        }
    }
    printGrid(game);
    LifeGUI::repaint();
}
/**
 * @brief openFile Prompts the user for a file to open up and calls make grid function to create the
 *                 grid
 * @return grid of booleans that is created from file selected by user
 */
Grid<bool> openFile(){
    Grid<bool> gameOfLife(3,3);
    ifstream infile;
    promptUserForFile(infile, "Grid Input File Name?");
    makeGrid(infile, gameOfLife);
    infile.close();
    return gameOfLife;

}
/**
 * @brief checkState Helper function to tick, will see if a cell is occupied
 *        if the cell does not exist, will wrap around and check that cell
 * @param row row of grid to be checked
 * @param col column of grid to be checked
 * @param game grid of booleans to be used as game board
 * @return bool if the space in the grid is occupied
 */
bool checkState(int row, int col, Grid <bool>& game){
    //check this state first because it will be the most common occurence
    if (game.inBounds(row,col)){
        return game[row][col];
    }
    else if (row<0 && col<0){
        row = game.numRows()-1;
        col = game.numCols()-1;
    }
    else if (row >= game.numRows() && col>= game.numCols()){
        row = 0;
        col = 0;
    }
    else if (row >= game.numRows() && col <0){
        row = 0;
        col = game.numCols()-1;
    }
    else if (row <0 && col >= game.numCols()){
        row = game.numRows()-1;
        col=0;
    }
    else if (row<0){
        row = game.numRows()-1;
     }
    else if(row>= game.numRows()){
        row = 0;
    }
    else if (col<0){
        col = game.numCols()-1;
     }
    else {
        col = 0;
    }
    return game[row][col];
}

/**
 * @brief takeAction Helper function to tick, decides what happens to each space depending on
 *        how many cells boardering it are occupied
 * @param count - number of cells occupied next to the cell given
 * @param gameOfLife - original grid of the past generation
 * @param newGame - grid of cells that is changed to the next generation, so that changing cells in the original
 *                  does not affect the creation of the next generation
 * @param r - row of cell
 * @param c - column of cell
 */
void takeAction(int count, Grid <bool> &gameOfLife, Grid<bool> &newGame, int r, int c){
    if (count == 0 || count  == 1){
        newGame[r][c] = false;
    }
    else if(count ==2){
        if(gameOfLife[r][c]){
            newGame[r][c] =true;
            LifeGUI::fillCell(r,c);
        }
        else{
            newGame[r][c] = false;
        }
    }
    else if(count == 3){
        newGame[r][c] = true;
        LifeGUI::fillCell(r,c);
    }
    else {
        newGame[r][c] = false;
    }
}
/**
 * @brief tick This function runs through one generation of the colony
 * @param gameOfLife - original grid of past generation
 */
Grid <bool> tick(Grid <bool> &gameOfLife){
    int count = 0;
    LifeGUI::clear();
    Grid <bool> newGame(gameOfLife.numRows(), gameOfLife.numCols());
    //iterate through the grid and see how many surrounding cells are occupied
    for (int r = 0; r< gameOfLife.numRows(); r++){
        for (int c = 0; c < gameOfLife.numCols(); c++){
            //check each neighboring cell, including diagonals
            if (checkState(r,c+1,gameOfLife)){
                count++;
            }
            if (checkState(r,c-1,gameOfLife)){
                count++;
            }
            if (checkState(r-1,c+1,gameOfLife)){
                count++;
            }
            if (checkState(r-1,c,gameOfLife)){
                count++;
            }
            if (checkState(r-1,c-1,gameOfLife)){
                count++;
            }
            if (checkState(r+1,c+1,gameOfLife)){
                count++;
            }
            if (checkState(r+1,c,gameOfLife)){
                count++;
            }
            if (checkState(r+1,c-1,gameOfLife)){
                count++;
            }
           takeAction(count, gameOfLife, newGame, r, c);
           count =0;
        }
    }
    LifeGUI::repaint();
    gameOfLife = newGame;
    printGrid(newGame);
    return newGame;
}
/**
 * @brief animate Allows the user to run through multiple generations of the colony with one command, with pauses in between
 * @param num number of generations to run through
 * @param gameOfLife Grid to be changed
 */
void animate(int num, Grid <bool> &gameOfLife){
    if(num >0){
        for (int i = 0; i< num; i++){
            tick(gameOfLife);
            pause(100);
            clearConsole();
        }
    }
    else{
        cout << "Illegal input. Try again." << endl;
    }
}

/**
 * @brief repeat Allows the program to repeat with a new file after the user chooses to quit
 */
void repeat(){
    Grid <bool> gameOfLife = openFile();
    prompt(gameOfLife);


}

/**
 * @brief prompt This function prompts the user for which action they would like to take next
 * @param gameOfLife grid to be changed as generations move
 */
void prompt( Grid <bool>& gameOfLife){
    string input = " ";
    while (input != "q"){
        input = getLine("a)nimate, t)ick, q)uit?");
        for (int i = 0; i<input.length(); i++){
            input[i] = tolower(input[i]);
        }

        if (input == "a"){
            int num = getInteger("Now many generations?");
            animate(num, gameOfLife);
        }
        else if(input =="t"){
            tick(gameOfLife);
        }
        else if (input == "q"){
            if(getYesOrNo("Load another file? (y/n)")){
                repeat();
            }
        }
        else{
            cout << "Invalid choice; please try again." <<endl;
        }
    }
}

/**
 * @brief printGrid Prints the new grid to the console using the boolean entries
 * @param newGame Grid to be printed
 */
void printGrid(Grid<bool> &newGame){
    for (int r = 0; r < newGame.numRows(); r++){
        for (int c = 0; c < newGame.numCols(); c++){
            if( newGame[r][c]){
                cout << "X";
            }
            else{
                cout << "-";
            }
        }
        cout << "\n";
    }
    cout << "\n";
}













