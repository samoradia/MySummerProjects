//Saagar Moradia
//9 August 2018
//CS106B
//LineManager.cpp
//This function implemenets functions and helper functions to allow the browser to paint the lines that are on screen
#include "LineManager.h"
using namespace std;

LineManager::LineManager(const Vector<Line *>& lines) {
    if(lines.size() >0){
    int end = lines.size()-1;
    int start = 0;
    //call helper function to initialize BST
    root = LineManagerHelper(lines, start, end);
    } else {
        root = nullptr;
    }
}
LineManager::~LineManager() {
    Node* hold = root;
    DestructorHelper(hold);
}

double LineManager::contentHeight() const {
    Node* hold = root;
    if(hold != nullptr){
         while(hold->right != nullptr){
            hold = hold->right;
        }
            //can assume the starting y value is 0
            return hold->line->highY();
    } else {
        return 0;
    }
}

Vector<Line *> LineManager::linesInRange(double lowY, double highY) const {
    Node * hold  = root;
    Vector<Line*> inLine;
    if(hold != nullptr){
        RangeHelper(lowY, highY, hold, inLine);
    }
    return inLine;
}

Line* LineManager::lineAt(double y) const {
    Node* hold = root;
    return LineAtHelper(y, hold);
}
LineManager::Node* LineManager::LineManagerHelper(const Vector<Line *>& lines, int start, int end){
    //base case
    if(start > end){
        return nullptr;
    }
    //subtree's root should be in the middle for it to be balanced
    int mid = (start+end)/2;
    Node* hold = new Node{lines[mid],nullptr, nullptr};
    hold->left = LineManagerHelper(lines, start, mid-1);
    hold->right = LineManagerHelper(lines, mid+1, end);
    return hold;

}
void LineManager::RangeHelper( double min,  double max,  Node* root,  Vector<Line *>& lines) const{
    if(root != nullptr){
        //if the range is completely out of range of the current line, check other ones
         if ((root->line->highY() <= min )||( root->line->lowY() >= max)){
            RangeHelper(min, max, root->left,lines);
            RangeHelper(min, max, root->right,lines);
        } else {
             //line is in the range, add it and check others around it
            RangeHelper(min, max, root->left,lines);
            lines.add(root->line);
            RangeHelper(min, max, root->right,lines);


        }
    }
}
Line* LineManager::LineAtHelper(double y, Node* root) const{
    if(root != nullptr){
        if(root->line->highY() >= y && root->line->lowY() <= y){
            return root->line;
        } else {
            //simply search the tree for the y value
            LineAtHelper(y, root->left);
            LineAtHelper(y, root->right);
        }
    }
    return nullptr;
}
void LineManager::DestructorHelper(Node* root){

    if (root == nullptr){
        delete root;
    } else if(root->left == nullptr || root->right == nullptr){
        delete root->line;
    } else {
        DestructorHelper(root->left);
        DestructorHelper(root->right);
    }
}
