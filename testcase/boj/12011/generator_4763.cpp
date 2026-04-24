#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cows
    int N = rnd.next(3, 10);

    // Number of clusters for diversity
    int maxClusters = min(3, N/2);
    int K = rnd.next(1, maxClusters);

    // Partition N into K positive cluster sizes
    vector<int> sz(K, 1);
    int rem = N - K;
    for (int i = 0; i < rem; i++) {
        int j = rnd.next(0, K - 1);
        sz[j]++;
    }

    // Horizontal or vertical cluster layout
    bool horiz = rnd.next() < 0.5;

    // Generate cluster centers with separation
    vector<pair<int,int>> centers(K);
    int gap = rnd.next(20, 100);
    for (int i = 0; i < K; i++) {
        if (horiz) {
            int cx = rnd.next(1, 100) + i * gap;
            int cy = rnd.next(1, 100);
            centers[i] = {cx, cy};
        } else {
            int cx = rnd.next(1, 100);
            int cy = rnd.next(1, 100) + i * gap;
            centers[i] = {cx, cy};
        }
    }

    // Generate unique points
    set<pair<int,int>> used;
    vector<pair<int,int>> pts;
    for (int i = 0; i < K; i++) {
        int cx = centers[i].first;
        int cy = centers[i].second;
        // Alignment probabilities vary per cluster
        double alignProbX = rnd.next() * 0.3; // up to 0.3
        double alignProbY = rnd.next() * 0.3;
        for (int t = 0; t < sz[i]; t++) {
            pair<int,int> p;
            // try until unique
            do {
                int x = (rnd.next() < alignProbX ? cx : cx + rnd.next(-10, 10));
                int y = (rnd.next() < alignProbY ? cy : cy + rnd.next(-10, 10));
                x = max(1, x);
                y = max(1, y);
                p = {x, y};
            } while (used.count(p));
            used.insert(p);
            pts.push_back(p);
        }
    }

    // Shuffle to randomize order
    shuffle(pts.begin(), pts.end());

    // Output result
    println(N);
    for (auto &p : pts)
        println(p.first, p.second);

    return 0;
}
