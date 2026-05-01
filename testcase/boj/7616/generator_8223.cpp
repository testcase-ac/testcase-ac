#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int T = rnd.next(3, 5);
    for (int tc = 0; tc < T; tc++) {
        int type = rnd.next(1, 4);
        int N, maxPaths;
        vector<vector<int>> adj;
        if (type == 1) {
            // Clique
            N = rnd.next(3, 8);
            maxPaths = N - 2;
            adj.assign(N+1, vector<int>());
            for (int i = 1; i <= N; i++)
                for (int j = 1; j <= N; j++)
                    if (i != j)
                        adj[i].push_back(j);
        } else if (type == 2) {
            // Simple path 1 - 3 - 4 - ... - N - 2
            N = rnd.next(3, 10);
            maxPaths = 1;
            adj.assign(N+1, vector<int>());
            vector<int> seq;
            seq.push_back(1);
            for (int i = 3; i <= N; i++) seq.push_back(i);
            seq.push_back(2);
            for (int i = 0; i + 1 < (int)seq.size(); i++) {
                int u = seq[i], v = seq[i+1];
                adj[u].push_back(v);
                adj[v].push_back(u);
            }
        } else if (type == 3) {
            // Star via mid nodes
            N = rnd.next(4, 10);
            maxPaths = N - 2;
            adj.assign(N+1, vector<int>());
            for (int m = 3; m <= N; m++) {
                adj[1].push_back(m);
                adj[m].push_back(1);
                adj[2].push_back(m);
                adj[m].push_back(2);
            }
        } else {
            // Random tree, ensure 2 connected to 1
            N = rnd.next(5, 12);
            maxPaths = 1;
            adj.assign(N+1, vector<int>());
            // connect 2 to 1
            adj[1].push_back(2);
            adj[2].push_back(1);
            for (int i = 3; i <= N; i++) {
                int p = rnd.next(1, i-1);
                adj[i].push_back(p);
                adj[p].push_back(i);
            }
        }
        // Choose K based on possible/impossible
        bool possible = rnd.next(0,1);
        int K;
        if (possible) {
            K = rnd.next(1, maxPaths);
        } else {
            K = rnd.next(maxPaths + 1, maxPaths + 2);
        }
        // Output this test case
        println(K, N);
        for (int i = 1; i <= N; i++) {
            shuffle(adj[i].begin(), adj[i].end());
            println(adj[i]);
        }
    }
    println(0, 0);
    return 0;
}
