#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of vertices
    int N = rnd.next(3, 12);
    int maxEdges = N * (N - 1) / 2;
    // Hyper-parameter to bias towards sparse or dense graphs
    int densityBias = rnd.next(-2, 2);
    // M in [0, maxEdges], biased by densityBias
    int M = rnd.wnext(maxEdges + 1, densityBias);

    // Choose three distinct special vertices B, E, H
    vector<int> verts(N);
    for (int i = 0; i < N; i++) verts[i] = i + 1;
    shuffle(verts.begin(), verts.end());
    int B = verts[0], E = verts[1], H = verts[2];

    // Build all possible edges
    vector<pair<int,int>> allEdges;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            allEdges.emplace_back(i, j);
        }
    }
    shuffle(allEdges.begin(), allEdges.end());
    allEdges.resize(M);

    // Print header
    println(N, M, B, E, H);

    // Hyper-parameter for weight distribution
    double heavyProb = rnd.next();

    // Print edges with weights
    for (auto &e : allEdges) {
        int u = e.first, v = e.second;
        int t;
        if (rnd.next() < heavyProb) {
            // heavy edge
            t = rnd.next(1000, 1000000);
        } else {
            // light edge
            t = rnd.next(1, 999);
        }
        println(u, v, t);
    }

    return 0;
}
