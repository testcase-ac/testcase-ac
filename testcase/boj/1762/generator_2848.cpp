#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    int N = rnd.next(1, 10);
    vector<pair<int,int>> edges;

    // With some probability generate an outerplanar graph (cycle + non-crossing diagonals)
    if (N >= 3 && rnd.next() < 0.7) {
        // Add cycle edges
        for (int i = 1; i <= N; i++) {
            int j = (i == N ? 1 : i + 1);
            edges.emplace_back(i, j);
        }
        // Build all possible diagonals in the convex N-gon
        vector<pair<int,int>> diags;
        for (int i = 1; i <= N; i++) {
            for (int j = i + 1; j <= N; j++) {
                if (j == i + 1) continue;       // skip cycle edges
                if (i == 1 && j == N) continue; // skip closing cycle edge
                diags.emplace_back(i, j);
            }
        }
        shuffle(diags.begin(), diags.end());
        double pDiag = rnd.next(); // probability to attempt adding each diagonal
        vector<pair<int,int>> added;
        for (auto d : diags) {
            if (rnd.next() >= pDiag) continue;
            bool ok = true;
            // check crossing with any already added diagonal
            for (auto &s : added) {
                int i = d.first, j = d.second, u = s.first, v = s.second;
                if ((i < u && u < j && j < v) || (u < i && i < v && v < j)) {
                    ok = false;
                    break;
                }
            }
            if (ok) {
                added.push_back(d);
                edges.push_back(d);
            }
        }
    }
    else {
        // Otherwise generate a random tree (always planar, no triangles)
        for (int i = 2; i <= N; i++) {
            int p = rnd.next(1, i - 1);
            edges.emplace_back(i, p);
        }
    }

    // Normalize edge ordering and shuffle
    for (auto &e : edges) {
        if (e.first > e.second) swap(e.first, e.second);
    }
    shuffle(edges.begin(), edges.end());

    // Output
    println(N, edges.size());
    for (auto &e : edges) println(e.first, e.second);

    return 0;
}
