//Saagar Moradia
//26 July 2018
//CS106B
//Marble Solitaire
//This program will attempt to see if a board can be solved from its current state using recursive backtracking
#include "grid.h"
#include "vector.h"
#include "marbletypes.h"
#include "compression.h"
#include "marbleutil.h"
#include "set.h"
using namespace std;
bool solvePuzzleHelper(Grid<Marble>& board, int marbleCount, Vector<Move>& moveHistory, Set<BoardEncoding> &boardState);
/**
 * @brief solvePuzzle - this function calls a helper function to see if a board can be solved
 * @param board - grid of marbles
 * @param marbleCount- number of marbles left on the board
 * @param moveHistory - vector of moves that have been taken
 * @return - bool if the board can be solved
 */
bool solvePuzzle(Grid<Marble>& board, int marbleCount, Vector<Move>& moveHistory) {
    Set<BoardEncoding> boardState;
    return solvePuzzleHelper(board, marbleCount, moveHistory, boardState);
}
/**
 * @brief solvePuzzleHelper - this helper function will recursively check all possible moves on the board to see if it is solvable
 * @param board - grid of marbles
 * @param marbleCount - number of marbles left on the board
 * @param moveHistory - vector of moves that have been taken
 * @param boardState - all previous boards that have been explored
 * @return - bool if the board can be solved
 */
bool solvePuzzleHelper(Grid<Marble> &board, int marbleCount, Vector<Move> &moveHistory, Set<BoardEncoding> &boardState){
    //base case
    if(marbleCount == 1){
        return true;
        //recursive case
    } else {
        //board has been explored already
        BoardEncoding compBoard = compressBoard(board);
        if(boardState.contains(compBoard)){
            return false;
        }
        boardState.add(compBoard);
        Vector<Move> moves = findPossibleMoves(board);
        //iterate through all possible moves and add to move vector and do the move
        for(int i = 0; i < moves.size(); i ++){
            moveHistory.add(moves[i]);
            makeMove(moves[i], board);
            if(solvePuzzleHelper(board, marbleCount -1, moveHistory, boardState)){
                return true;
            }
            //if path is false, undo move and remove the last move object from vector
            moveHistory.remove(moveHistory.size()-1);
            undoMove(moves[i], board);

        }
        return false;
    }
}
