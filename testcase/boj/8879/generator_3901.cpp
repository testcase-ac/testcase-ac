#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of intersections
    int N = rnd.next(2, 10);
    // Number of commuters
    int C = rnd.next(1, min(20, 2 * N));

    // Build a random spanning tree to ensure connectivity
    vector<pair<int,int>> edges;
    edges.reserve(N - 1 + 5);
    vector<vector<bool>> used(N + 1, vector<bool>(N + 1, false));
    for (int i = 2; i <= N; ++i) {
        int p = rnd.next(1, i - 1);
        edges.emplace_back(p, i);
        used[p][i] = used[i][p] = true;
    }

    // Add a few extra edges (up to 5) for diversity, avoiding duplicates
    int Mmax = N * (N - 1) / 2;
    int extras_max = Mmax - (N - 1);
    int extras_cnt = rnd.next(0, min(extras_max, 5));
    vector<pair<int,int>> candEx;
    candEx.reserve(extras_max);
    for (int i = 1; i <= N; ++i) {
        for (int j = i + 1; j <= N; ++j) {
            if (!used[i][j]) candEx.emplace_back(i, j);
        }
    }
    shuffle(candEx.begin(), candEx.end());
    for (int i = 0; i < extras_cnt; ++i) {
        edges.push_back(candEx[i]);
    }

    int M = edges.size();

    // Choose a weight mode for travel times: uniform [1,10], [1,3], or [8,10]
    int mode = rnd.next(0, 2);
    vector<int> weights(M);
    for (int i = 0; i < M; ++i) {
        if (mode == 0)        weights[i] = rnd.next(1, 10);
        else if (mode == 1)   weights[i] = rnd.next(1, 3);
        else                  weights[i] = rnd.next(8, 10);
    }

    // Generate starting intersections for commuters
    vector<int> starts(C);
    if (rnd.next() < 0.3) {
        // All from one random non-downtown node
        int s = rnd.next(2, N);
        for (int i = 0; i < C; ++i) starts[i] = s;
    } else {
        // Each chosen uniformly
        for (int i = 0; i < C; ++i) {
            starts[i] = rnd.next(1, N);
        }
    }

    // Output
    println(N, M, C);
    for (int i = 0; i < M; ++i) {
        println(edges[i].first, edges[i].second, weights[i]);
    }
    println(starts);

    return 0;
}
