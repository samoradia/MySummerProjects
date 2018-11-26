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
void animate();
void tick(Grid <bool> &gameOfLife);
Grid<bool> openFile();
void run();
void intro();
void makeGrid(ifstream &infile, Grid<bool> &game);
bool checkState(int row, int col, Grid <bool>& game);
void takeAction(int count, Grid <bool>& Newgame, int row, int col);

int main() {
    intro();
    Grid <bool> gameOfLife = openFile();
    //cout << gameOfLife << "before" <<endl;
    tick(gameOfLife);
    cout << gameOfLife << "after" << endl;
    //cout << "Have a nice Life!" << endl;
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
         << "* A cell with 4 or more neighbors dies." << endl;
}
/**
 * @brief Helper function to openFile(), takes the input from the file and turns it into a Grid
 * @return Grid gameOfLife
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
    //the file will always have 2 more rows than the number of rows in the grid
    //all other info is irrelevant to the program and will be ignored, it will stop after the number of rows
    for(int i=0;i<row;i++){
        getline(infile, line);
        for(int j = 0; j < col;j++){
            if(line[j] == 'X'){
                game[i][j] = true;
            }
            else{
                game[i][j] = false;
            }
        }
    }
}

Grid<bool> openFile(){
    Grid<bool> gameOfLife(3,3);
    ifstream infile;
    infile.open("format.txt");
    //promptUserForFile(infile, "Please select the file to open"); FIXXX
    makeGrid(infile, gameOfLife);
    return gameOfLife;

}
/**
 * @brief tick This function runs through one generation of the colony
 */
void tick(Grid <bool> &gameOfLife){
    int count = 0;
    Grid <bool> newGame(gameOfLife.numRows(), gameOfLife.numCols());
    //iterate through the grid and see how many surrounding cells are occupied
    for (int r = 0; r< gameOfLife.numRows(); r++){
        for (int c = 0; c < gameOfLife.numCols(); c++){
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
           takeAction(count, gameOfLife, r, c);
        }
    }
}
/**
 * @brief checkState Helper function to tick, will see if a cell is occupied
 *        if the cell does not exist, will wrap around and check that cell
 * @param row row of grid to be checked
 * @param col column of grid to be checked
 * @param game grid of booleans to be used as game board
 */
bool checkState(int row, int col, Grid <bool>& game){
    //check this state first because it will be the most common occurence
    if (game.inBounds(row,col)){
        if (game[row][col]){
            return true;
        }
        return false;
    }
    else if (row<0){
        row = game.numRows();
     }
    else if(row>= game.numRows()){
        row = 0;
    }
    else if (col<0){
        col = game.numCols();
     }
    else {
        col = 0;
    }
    //will have to recheck with changed row/col indicies
    if (game.inBounds(row,col)){
        if (game[row][col]){
            return true;
        }
        return false;
    }
    return false;
}
/**
 * @brief takeAction Helper function to tick, decides what happens to each space depending on
 *        how many cells boardering it are occupied
 * @param count - number of cells occupied next to the cell given
 * @param game - grid of cells
 * @param r - row of cell
 * @param c - column of cell
 */
void takeAction(int count, Grid<bool>& newGame, int r, int c){
    if (count == 0 || count  == 1){
        newGame[r][c] = false;
    }

    else if(count == 3){
        newGame[r][c] = true;
    }
    else if(count >=4){
        newGame[r][c] = false;
    }
}













