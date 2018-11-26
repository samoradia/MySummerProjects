#include <iostream>
#include "console.h"
#include "vector.h"
#include "error.h"
#include "filelib.h"
#include "gwindow.h"
#include "set.h"
#include "graph.h"
#include "priorityqueue.h"
#include "hashmap.h"

using namespace std;
struct Edge{
    int start;
    int end;
    string name;
    int cost;
};
/*
bool isPalindrome(string s){
    if (s.length()<= 1){
        return true;
    }
    else {
        char first = s[0];
        char last = s[s.length()-1];
        if (first == last){
            return isPalindrome(s.substr(1,s.length()-2));
        }
        else{
            return false;
        }
    }
}
int binaryToDecimal(string bin){
    if (bin.length() ==1){
        return bin[0] - '0';
    } else {
        return 2* binaryToDecimal(bin.substr(0, bin.length()-1))
        +binaryToDecimal(bin.substr(bin.length()-1));
    }
}

double expon(double num, int exp){
    if (exp < 0){
        error("Exponent must be positive or 0");
    }
    if (exp < 1){
        return 1;
    } else {
        return num * (expon(num, exp-1));
    }
}
void reverseLines(ifstream& input){
    string firstLine;
    if(getLine(input, firstLine)){
        reverseLines(input);
        cout << firstLine <<endl;
    }

}
void crawl(string name, string indent = ""){//using default parameter to make it optional
    cout << indent << getTail(name) <<endl;
    if (isDirectory(name)){
        cout << getTail(name) <<endl;
        indent += "/t";
        for (string subfile : listDirectory(name)){
            crawl(name+ "\\"+subfile, indent);
        }
    }
}
void cantorSet(GWindow& window, int x, int y, int length, int levels){
    if (level > 0){
        window.drawLine(x,y, x+length, y);
        cantorSet(window, x, y+CANTOR_SPACING, length /3, levels-1);
        cantorSet(window, x + length - length /3, y+CANTOR_SPACING, length /3, levels-1);

    }
}

GPoint ksLine(GWindow&	gw,	GPoint &pt,	int	size,	int	t,	int	levels)	{
    if	(levels	==	1)	{
        return	gw.drawPolarLine(pt, size, t);
    }	else	{
            pt	=	ksLine(gw,	pt,	size/3,	t,	levels	-	1);
            pt	=	ksLine(gw,	pt,	size/3,	t+60,levels	-	1);
            pt	=	ksLine(gw,	pt,	size/3,	t-60,levels	-	1);
            pt = 	ksLine(gw,	pt,	size/3,	t, levels -	1);
            return pt;
    }
}
void kochSnowflake(GWindow&	gw,	int	x,	int	y,	int	size,	int	levels)	{
    GPoint pt(x, y);
    pt	=	ksLine(gw,	pt,	size, 0, levels);
    pt	=	ksLine(gw,	pt,	size, -120,	levels);
    pt	=	ksLine(gw,	pt,	size, 120, levels);
}

//exhaustive search
string printAllBinary(int num, string decisionSoFar = ""){
    if(decisionSoFar.length() == num){
        decisionSoFar;
        cout << decisionSoFar <<endl;
    } else {
        for (int i = 0; i <= 9; i++){//change this to change what is printed all of
            printAllBinary(num, decisionSoFar + integerToString(i));
        }
    }

}
diceSumHelper(int dice, int desiredSum, Vector <int>& decisionsSoFar){
    if (decisionsSoFar.size() == dice){
        if(sum(decisionsSoFar) == desiredSum){
            cout << decisionsSoFar <<endl;
        }else {
            //nothing
        }
        return;
    } else{
        for (int i = 1; i<=6; i++){
            decisionsSoFar += i;
            diceSumHelper(dice, desiredSum, decisionsSoFar);
            decisionsSoFar = decisionsSoFar.subList(0, decisionsSoFar.size() -1)
        }
    }
}

//backtrapping
void diceSum(int dice, int desiredSum){
    diceSumHelper(dice, desiredSum, )
}
*/
Set<string> kruskals(Vector<Edge> &edges){
    Set<string> mst;
    PriorityQueue<Edge> pqueue;
    HashMap<int, Set<int>> clusters;
    for (Edge edge :edges){
        pqueue.enqueue(edge, edge.cost);
        clusters[edge.start] = {edge.start};
        clusters[edge.end] = {edge.end};
    }

    while(!pqueue.isEmpty()){
        Edge edge = pqueue.dequeue();
        if(!clusters[edge.start].contains(edge.end)){
            Set<int> mergedCluster = clusters[edge.start] + clusters[edge.end];
            for(int node : mergedCluster){
            clusters[node] = mergedCluster;
            }
            mst.add(edge);
        }
    }
    return mst;
}
int main() {
    cout << "Hello, world!" << endl;
    printAllBinary(2);
    return 0;
}
