#include "testlib.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    
    // Choose a small number of cities.
    int n = rnd.next(2, 10);
    
    // Pick two distinct cities for our query.
    int A = rnd.next(1, n);
    int B = rnd.next(1, n);
    while(A == B) {
        B = rnd.next(1, n);
    }
    
    // Decide on a simple directed path from A to B.
    // We'll include a random number of intermediate cities (which can be zero).
    int numIntermediate = rnd.next(0, n - 2);  // at most n-2 extra nodes
    vector<int> candidates;
    for (int i = 1; i <= n; i++){
        if(i != A && i != B) {
            candidates.push_back(i);
        }
    }
    shuffle(candidates.begin(), candidates.end());
    
    // Build the path: start with A, then some intermediate nodes, then B.
    vector<int> path;
    path.push_back(A);
    for (int i = 0; i < numIntermediate; i++){
        path.push_back(candidates[i]);
    }
    path.push_back(B);
    
    // The number of edges in the path is fixed.
    int pathEdges = path.size() - 1;
    
    // Add some extra random edges for variety.
    int extraEdges = rnd.next(0, 5);
    int m = pathEdges + extraEdges;
    
    println(n);
    println(m);
    
    // Output the path edges to guarantee connectivity from A to B.
    for (int i = 0; i < pathEdges; i++){
        int u = path[i], v = path[i+1];
        int cost = rnd.next(1, 100); // positive cost for the path
        println(u, v, cost);
    }
    
    // Output extra random edges.
    for (int i = 0; i < extraEdges; i++){
        int u = rnd.next(1, n);
        int v = rnd.next(1, n);
        while(u == v) { // ensure no self-loop
            v = rnd.next(1, n);
        }
        int cost = rnd.next(0, 100); // cost can be 0 here
        println(u, v, cost);
    }
    
    // Finally, output the query: starting city A and destination city B.
    println(A, B);
    
    return 0;
}
