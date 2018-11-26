//Saagar Moradia
//CS106B
//Floodplain
//Given a Floodplain object, and a sealevel height, this program will be able to simulate the change in geography due to the height
//This program can be represented as a graph by utilizing the fact that each individual grid member is a node of the graph, ands its connections with
//its neighbors are the edges of the graph. Utilizing these connections can make checking for floods much more simple
//Sources:
//
#include "WaterLevel.h"
using namespace std;

/**
 * This function will look at the given row/col pair in floodplain, and check if its height is less than the water level, if it is, it is marked true,
 * and its neighbors are recursively checked until all tiles are checked or no more tiles can be flooded.
 */
void simulateFloodHelper(const Floodplain& floodplain, int row, int col, double height,
                         Grid<bool>& result, Grid<bool>& marked){
    GridLocation check = {row, col};

    if (!floodplain.heights.inBounds(check)){
        return;
    }
    if (marked[row][col]){
        return;
    }
    if (floodplain.heights[row][col] > height){
        //grid already initialized to false
        return;
    } else {
        result[row][col] = true;
        marked[row][col] = true;
        //check the neighbors recusively
        for(int i = -1; i<=1; i+=2){
            simulateFloodHelper(floodplain, row+i, col, height, result, marked);
            simulateFloodHelper(floodplain, row, col+i, height, result, marked);

        }
    }
}
/**
 * Given a floodplain and an altitude, returns a Grid<bool> indicating whether each cell
 * is under water. Cells under water are marked true; cells above water are marked false.
 *
 * Remember that water can only flow in cardinal directions (up, down, left, and right),
 * not diagonally.
 *
 * @param floodplain The plain to flood.
 * @param height The water height, in meters.
 * @return A Grid indicating which cells are flooded.
 */
Grid<bool> simulateFlood(const Floodplain& floodplain, double height) {
    Grid<bool> result;
    Grid<bool> marked;
    result.resize(floodplain.heights.numRows(),floodplain.heights.numCols());
    marked.resize(floodplain.heights.numRows(),floodplain.heights.numCols());
    for(int i = 0; i<floodplain.waterSources.size(); i++){
        //start with each floodpoint
        int row = floodplain.waterSources[i].row;
        int col = floodplain.waterSources[i].col;
        simulateFloodHelper(floodplain, row, col, height, result, marked);

    }
    return result;
}


