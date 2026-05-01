#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(5, 15);
    int R = rnd.next(1, N);
    // Build all possible edges
    vector<pair<int,int>> edgesAll;
    for (int i = 1; i <= N; i++)
        for (int j = i + 1; j <= N; j++)
            edgesAll.emplace_back(i, j);
    vector<pair<int,int>> edges;
    // Choose graph type for variability
    int gtype = rnd.next(1, 4);
    if (gtype == 1) {
        // Tree (connected, N-1 edges)
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i - 1);
            edges.emplace_back(p, i);
        }
    } else if (gtype == 2) {
        // Sparse forest (disconnected), M from 1 to N-2
        int M = rnd.next(1, N - 2);
        shuffle(edgesAll.begin(), edgesAll.end());
        edges.assign(edgesAll.begin(), edgesAll.begin() + M);
    } else if (gtype == 3) {
        // Moderate random graph, M from N-1 to min(all, 2*N)
        int ub = min((int)edgesAll.size(), 2 * N);
        int M = rnd.next(N - 1, ub);
        shuffle(edgesAll.begin(), edgesAll.end());
        edges.assign(edgesAll.begin(), edgesAll.begin() + M);
    } else {
        // Complete graph
        edges = edgesAll;
    }
    // Randomize input order
    shuffle(edges.begin(), edges.end());
    int M = edges.size();
    println(N, M, R);
    for (auto &e : edges) println(e.first, e.second);
    return 0;
}
