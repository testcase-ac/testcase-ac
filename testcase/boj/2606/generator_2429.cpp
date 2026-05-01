/* generator code */
#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of computers between 2 and 10
    int N = rnd.next(2, 10);
    // Maximum number of undirected edges
    int maxM = N * (N - 1) / 2;
    int M = rnd.next(0, maxM);

    // Build all possible undirected edges (i<j)
    vector<pair<int,int>> edges;
    for (int i = 1; i <= N; i++)
        for (int j = i + 1; j <= N; j++)
            edges.emplace_back(i, j);

    // Shuffle and take first M
    shuffle(edges.begin(), edges.end());
    edges.resize(M);

    // With some probability flip each edge orientation
    double flipProb = rnd.next(0.0, 1.0);

    // Output
    println(N);
    println(M);
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        if (rnd.next() < flipProb) swap(u, v);
        println(u, v);
    }
    return 0;
}
