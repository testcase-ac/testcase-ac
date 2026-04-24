#include "testlib.h"
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]){
    registerGen(argc, argv, 1);
    
    // We choose T = 2 test cases for a small, easily verifiable input.
    int T = rnd.next(1, 2);
    println(T);
    
    for (int tc = 0; tc < T; tc++){
        int N = rnd.next(2, 8);
        
        vector<int> times(N);
        for (int i = 0; i < N; i++){
            times[i] = rnd.next(0, 100);
        }
        
        vector<int> perm;
        for (int i = 1; i <= N; i++){
            perm.push_back(i);
        }
        shuffle(perm.begin(), perm.end());
        
        // Generate a DAG of dependency rules:
        // For each pair (perm[i], perm[j]) with i < j, add an edge with probability p.
        double p = rnd.next(0.01, 0.99);
        vector<pair<int,int>> edges;
        for (int i = 0; i < N; i++){
            for (int j = i + 1; j < N; j++){
                if(rnd.next() < p){
                    edges.push_back({perm[i], perm[j]});
                }
            }
        }
        // Ensure there is at least one dependency if possible.
        if (edges.empty()){
            edges.push_back({perm[0], perm[1]});
        }
        
        int K = edges.size();
        println(N, K);
        
        // Output building times.
        println(times);
        
        // Output the dependency rules.
        for (auto &e : edges){
            println(e.first, e.second);
        }
        
        // Choose a target building (W) randomly from 1 to N.
        int W = rnd.next(1, N);
        println(W);
    }
    return 0;
}
