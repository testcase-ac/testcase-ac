#include "testlib.h"
#include <vector>
#include <algorithm>
#include <utility>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of students
    int N = rnd.next(1, 10);
    // Maximum possible friendships
    int Mmax = N * (N - 1) / 2;
    // Weight parameter to bias toward sparse or dense graphs
    int densityWeight = rnd.next(-3, 3);
    // Number of edges
    int M = Mmax > 0 ? rnd.wnext(Mmax + 1, densityWeight) : 0;

    // Generate all possible undirected edges
    vector<pair<int,int>> edges;
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            edges.emplace_back(i, j);
        }
    }

    // Shuffle and pick M edges
    shuffle(edges.begin(), edges.end());
    edges.resize(M);

    // Sometimes swap the order A B -> B A in output
    double swapProb = rnd.next(0.0, 1.0);

    // Output
    println(N, M);
    for (auto &e : edges) {
        int u = e.first, v = e.second;
        if (rnd.next() < swapProb)
            println(v, u);
        else
            println(u, v);
    }

    return 0;
}
