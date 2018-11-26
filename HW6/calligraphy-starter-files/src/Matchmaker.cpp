//Saagar Moradia
//CS106B
//matchmaker
//This program will create a general function to find the maximum pairing in a bipartite graph
//Sources:
//Lecture slides 23
//Textbook pages 783-788
#include "Matchmaker.h"
using namespace std;

UnorderedPair matchMakeHelper(const BipartiteGraph& graph, HashSet<string>& seen, string& leftNode, int& matches);

/**
 * Given a bipartite graph, returns a maximum matching in that graph. If there are multiple
 * equally large maximum matchings, you can return any one of them.
 *
 * @param graph The graph in question.
 * @return One of its maximum matchings.
 */
Matching matchmake(const BipartiteGraph& graph) {
    Matching result;
    HashSet<string> seen;
    int matches = 0;
    for(string leftNode: graph.lhs){
        result.add(matchMakeHelper(graph, seen, leftNode, matches));
    }
    return result;
}
/**
 * This function will match a lhs node to a rhs node, if the match is possible. If it is not, then it will call a helper function to
 * break a connection
 */
UnorderedPair matchMakeHelper(const BipartiteGraph& graph, HashSet<string>& seen,  string& leftNode, int& matches){
    for(string rightNode:graph.rhs){
        if(!seen.contains(rightNode)){
            for(UnorderedPair edge: graph.edges){
                if(UnorderedPair{rightNode, leftNode} == edge){
                    seen.add(rightNode);
                    matches++;
                    return UnorderedPair{rightNode, leftNode};

                }
            }
        }
    }
    return {};
}
