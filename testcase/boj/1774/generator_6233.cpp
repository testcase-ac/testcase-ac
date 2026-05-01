#include "testlib.h"
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyperparameter: N from 2 to 15, bias towards smaller with wnext
    int N = max(2, rnd.wnext(15, -1));
    // Total possible undirected edges
    int totalPairs = N * (N - 1) / 2;

    // Generate coordinates with one of three patterns
    vector<pair<int,int>> coords(N);
    int pattern = rnd.next(0, 2);
    if (pattern == 0) {
        // Uniform random coords in [0,1000]
        for (int i = 0; i < N; i++) {
            coords[i].first = rnd.next(0, 1000);
            coords[i].second = rnd.next(0, 1000);
        }
    } else if (pattern == 1) {
        // Clustered points
        int ccount = rnd.next(1, min(N, 3));
        vector<pair<int,int>> cent;
        for (int i = 0; i < ccount; i++) {
            cent.emplace_back(rnd.next(0, 1000), rnd.next(0, 1000));
        }
        for (int i = 0; i < N; i++) {
            auto [cx, cy] = cent[i % ccount];
            int xlo = max(0, cx - 50), xhi = min(1000, cx + 50);
            int ylo = max(0, cy - 50), yhi = min(1000, cy + 50);
            coords[i].first = rnd.next(xlo, xhi);
            coords[i].second = rnd.next(ylo, yhi);
        }
    } else {
        // Grid points
        int g = int(ceil(sqrt(N)));
        int gap = rnd.next(10, 100);
        for (int i = 0; i < N; i++) {
            int r = i / g, c = i % g;
            coords[i].first = r * gap;
            coords[i].second = c * gap;
        }
    }

    // Determine M, number of pre-existing edges, ensure 1 <= M <= totalPairs
    int M;
    if (totalPairs < 4) {
        M = rnd.next(1, totalPairs);
    } else {
        int cat = rnd.next(0, 2);
        if (cat == 0) {
            int hi = min(totalPairs, N-1);
            M = rnd.next(1, max(1, hi));
        } else if (cat == 1) {
            int lo = min(N-1, totalPairs);
            int hi = totalPairs/2;
            if (lo > hi) lo = 1, hi = totalPairs;
            M = rnd.next(lo, max(lo, hi));
        } else {
            int lo = totalPairs/2 + 1;
            if (lo > totalPairs) lo = 1;
            M = rnd.next(lo, totalPairs);
        }
    }

    // Build all possible edges and pick M distinct ones
    vector<pair<int,int>> edges;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            edges.emplace_back(i, j);
        }
    }
    shuffle(edges.begin(), edges.end());
    edges.resize(M);

    // Output
    println(N, M);
    for (auto &p : coords) {
        println(p.first, p.second);
    }
    for (auto &e : edges) {
        println(e.first, e.second);
    }

    return 0;
}
