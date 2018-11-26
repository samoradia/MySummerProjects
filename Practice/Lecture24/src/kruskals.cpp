/*
 * CS 106B/X, Ashley Taylor
 * 
 * This program demonstrates implementing a graph algorithm from pseudocode
 * into code. Specifically, it contains the code implementation for Kruskal's
 * algorithm to find a minimum spanning tree.
 */

#include <iostream>
#include "console.h"
#include "vector.h"
#include "map.h"
#include "set.h"
#include "pqueue.h"
using namespace std;

/* A simple struct for an edge.
 * You could make this example more complicated with
 * more complex vertices, etc.
 */
struct Edge {
  int start;
  int end;
  string name;
  int cost;
};

/* This method implements Kruskal's algorithm and returns a set of strings
 * of edge names corresponding to the minimum spanning tree for the graph represented
 * by the edge list edges.
 */
Set<string> kruskals(Vector<Edge> &edges) {
    Set<string> result;
    // place all the edges in a priority queue based on edge.cost

    // initialize the clusters

    // while the priority queue is not empty
    // If e's endpoints aren't already connected,
        // add that edge into the minimum spanning tree.
    // Otherwise, skip the edge.


    return result;
}

int main() {
    // this graph corresponds to the graph from the lecture slides
    Vector<Edge> edges = {
        Edge{1, 2, "d", 4},
        Edge{1, 5, "a", 1},
        Edge{2, 5, "e", 5},
        Edge{2, 3, "i", 12},
        Edge{3, 5, "c", 3},
        Edge{3, 4, "h", 8},
        Edge{3, 6, "g", 7},
        Edge{3, 7, "n", 14},
        Edge{4, 7, "b", 2},
        Edge{5, 6, "f", 6},
        Edge{5, 8, "i", 9},
        Edge{6, 7, "r", 18},
        Edge{6, 8, "j", 10},
        Edge{7, 8, "m", 13},
        Edge{7, 9, "o", 15},
        Edge{8, 9, "k", 11},
        Edge{8, 10, "q", 17},
        Edge{9, 10, "p", 16}
    };
    cout << "Kruskal's Algorithm result: " << kruskals(edges) << endl;
    return 0;
}
