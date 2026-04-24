#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small number of vectors
    int N = rnd.next(1, 10);
    // Choose a coordinate bound for diversity
    vector<int> bounds = {5, 10, 20, 30};
    int B = rnd.any(bounds);
    // Three distribution types
    int distType = rnd.next(0, 2);

    vector<pair<int,int>> pts;
    if (distType == 0) {
        // Uniform random non-zero vectors in [-B, B]
        for (int i = 0; i < N; i++) {
            int x, y;
            do {
                x = rnd.next(-B, B);
                y = rnd.next(-B, B);
            } while (x == 0 && y == 0);
            pts.emplace_back(x, y);
        }
    } else if (distType == 1) {
        // Clustered around a random direction
        int cx, cy;
        do {
            cx = rnd.next(-B, B);
            cy = rnd.next(-B, B);
        } while (cx == 0 && cy == 0);
        int noise = max(1, B / 4);
        for (int i = 0; i < N; i++) {
            int t = rnd.next(1, B);
            int nx = rnd.next(-noise, noise);
            int ny = rnd.next(-noise, noise);
            int x = cx * t + nx;
            int y = cy * t + ny;
            if (x == 0 && y == 0) {
                // avoid zero vector
                x = (x == 0 ? 1 : x);
                y = (y == 0 ? 1 : y);
            }
            pts.emplace_back(x, y);
        }
    } else {
        // Points on axes
        for (int i = 0; i < N; i++) {
            if (rnd.next(0, 1)) {
                int v = rnd.any(vector<int>{-1, 1}) * rnd.next(1, B);
                pts.emplace_back(v, 0);
            } else {
                int v = rnd.any(vector<int>{-1, 1}) * rnd.next(1, B);
                pts.emplace_back(0, v);
            }
        }
    }

    // Shuffle order
    shuffle(pts.begin(), pts.end());

    // Output
    println(N);
    for (auto &p : pts) {
        println(p.first, p.second);
    }

    return 0;
}
