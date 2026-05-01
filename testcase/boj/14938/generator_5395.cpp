#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of regions (nodes)
    int N = rnd.next(2, 10);
    // Search range
    int m = rnd.next(1, 15);

    // Hyper-parameter for graph density: skew to sparse or dense
    int maxE = N * (N - 1) / 2;
    int capE = min(maxE, 15);
    int densityBias = rnd.next() < 0.5 ? -1 : 1;
    // Number of roads
    int r = rnd.wnext(capE, densityBias) + 1;

    // Hyper-parameter for item counts: skew to low or high
    int itemBias = rnd.next() < 0.5 ? -1 : 1;
    vector<int> items(N);
    for (int i = 0; i < N; i++) {
        // item count in [1,30], skewed
        items[i] = rnd.wnext(30, itemBias) + 1;
    }

    // Build all possible edges
    vector<pair<int,int>> allEdges;
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            allEdges.emplace_back(i, j);
        }
    }
    shuffle(allEdges.begin(), allEdges.end());

    // Pick first r edges
    allEdges.resize(r);

    // Hyper-parameter for edge weights: skew to short or long
    int weightBias = rnd.next() < 0.5 ? -1 : 1;

    // Output
    println(N, m, r);
    println(items);
    for (auto &e : allEdges) {
        int w = rnd.wnext(15, weightBias) + 1; // length in [1,15]
        println(e.first, e.second, w);
    }

    return 0;
}
