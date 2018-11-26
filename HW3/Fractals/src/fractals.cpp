//Saagar Moradia
//18 July 2018
//Fractal Program
//This program will allow the user to create either a sierpinski triangle or a recursive
//tree of order n using a GUI
//Sources:
//http://web.stanford.edu/class/cs106b/lectures/Lecture10/Lecture10.pdf
//https://en.wikipedia.org/wiki/Equilateral_triangle#Sides
//

#include "fractals.h"
#include "gwindow.h"
#include <cmath>
using namespace std;
GPoint drawBranch(GWindow& gw, GPoint pt, int size, int angle, int order);

/**
 * @brief drawSierpinskiTriangle This function will create a sierpinski triangle of order n
 * @param gw - graphics window to be printed onto
 * @param x - starting x position of top left
 * @param y - starting y position of top left of triangle
 * @param size - side length
 * @param order - order of triangle to be created
 */
void drawSierpinskiTriangle(GWindow& gw, double x, double y, double size, int order) {
    GPoint pt(x,y);
    //fail case
    if (order < 0 || x <0 || y < 0 || size < 0){
        throw "All values must be positive";
        //base case
    } else if(order == 1) {
        GPoint pt1 = gw.drawPolarLine(pt, size, 0);
        GPoint pt2 = gw.drawPolarLine(pt1, size, -120);
        gw.drawPolarLine(pt2, size, 120);
        //recursive case
    } else {
        //draw top right
        drawSierpinskiTriangle(gw, x + size/2, y, size / 2, order - 1);
        //draw top left
        drawSierpinskiTriangle(gw, x, y, size / 2, order - 1);
        //draw bottom
        drawSierpinskiTriangle(gw, x + size / 4, y + size * sqrt(3)/4, size / 2, order - 1);
    }
}
/**
 * @brief drawTree - This function will allow the user to create a binary tree of order n by calling a helper function
 * @param gw - window to be drawn on
 * @param x - x coordinate of the top of the box that will contain the tree
 * @param y - x coordinate of the top of the box that will contain the tree
 * @param size - size of the box that will contain the tree
 * @param order - order of the tree to be drawn
 */
void drawTree(GWindow& gw, double x, double y, double size, int order) {
    //get the start of tree to the position outlined in assignment sheet
    GPoint pt(x+size/2,y+size);
    if (order < 0 || x <0 || y < 0 || size < 0){
        throw "All values must be positive";
    } else {
        drawBranch(gw, pt, size/2, 90, order);
    }
}

GPoint drawBranch(GWindow &gw, GPoint pt, int size, int angle, int order){
    if(order ==1){
        gw.setColor("#2e8b57");
    } else {
        gw.setColor("#8b7765");
    }
    pt = gw.drawPolarLine(pt, size, angle);
    //GPoint hold = pt;
    if(order == 1){
       return pt;
     } else {
        for (int i = 0; i < 7; i ++){                
           drawBranch(gw, pt, size/2, angle-45, order-1);
           angle +=15;
        }
        angle = 0;
        return pt;
    }
}
