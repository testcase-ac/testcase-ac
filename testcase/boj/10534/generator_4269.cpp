#include "testlib.h"
#include <vector>
#include <array>
#include <algorithm>
using namespace std;

bool overlaps(const array<int,4>& a, const array<int,4>& b) {
    int x = a[0], y = a[1], w = a[2], h = a[3];
    int x2 = b[0], y2 = b[1], w2 = b[2], h2 = b[3];
    if (x + w <= x2 || x2 + w2 <= x) return false;
    if (y + h <= y2 || y2 + h2 <= y) return false;
    return true;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of rectangles
    int N = rnd.next(1, 10);
    int maxXY = 50;
    vector<array<int,4>> rects;
    // Hyperparameter for clustering
    double p_cluster = rnd.next(0.0, 1.0);
    if (N > 1 && rnd.next() < p_cluster) {
        int targetCluster = rnd.next(2, N);
        // Place first rectangle of cluster
        int w = rnd.next(1, 5), h = rnd.next(1, 5);
        int x = rnd.next(0, maxXY - w), y = rnd.next(0, maxXY - h);
        rects.push_back({x, y, w, h});
        // Directions for adjacency
        vector<pair<int,int>> dirs;
        for (int dx = -1; dx <= 1; dx++)
            for (int dy = -1; dy <= 1; dy++)
                if (dx != 0 || dy != 0)
                    dirs.emplace_back(dx, dy);
        // Build cluster
        for (int i = 1; i < targetCluster; i++) {
            int W = rnd.next(1, 5), H = rnd.next(1, 5);
            auto prev = rects.back();
            shuffle(dirs.begin(), dirs.end());
            bool placed = false;
            for (auto d : dirs) {
                int xi = prev[0] + d.first * prev[2];
                int yi = prev[1] + d.second * prev[3];
                if (xi < 0 || xi > maxXY - W || yi < 0 || yi > maxXY - H)
                    continue;
                array<int,4> cand = {xi, yi, W, H};
                bool ok = true;
                for (auto& ex : rects) {
                    if (overlaps(cand, ex)) { ok = false; break; }
                }
                if (ok) {
                    rects.push_back(cand);
                    placed = true;
                    break;
                }
            }
            if (!placed) break;
        }
    }
    // Fill remaining rectangles randomly without overlap
    int attempts = 0;
    while ((int)rects.size() < N && attempts < 10000) {
        int w = rnd.next(1, 5), h = rnd.next(1, 5);
        int x = rnd.next(0, maxXY - w), y = rnd.next(0, maxXY - h);
        array<int,4> cand = {x, y, w, h};
        bool ok = true;
        for (auto& ex : rects) {
            if (overlaps(cand, ex)) { ok = false; break; }
        }
        if (ok) rects.push_back(cand);
        attempts++;
    }
    // In rare case we couldn't place enough, adjust N
    N = (int)rects.size();
    // Shuffle output order
    shuffle(rects.begin(), rects.end());
    // Print
    println(N);
    for (auto& r : rects) {
        println(r[0], r[1], r[2], r[3]);
    }
    return 0;
}
