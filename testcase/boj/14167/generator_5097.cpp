#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of cows
    int N = rnd.next(2, 10);
    vector<pair<int,int>> cows(N);

    // Scenario selection for diversity
    // 0: uniform random
    // 1: clusters
    // 2: horizontal line with noise
    // 3: vertical line with noise
    int scenario = rnd.next(0, 3);
    if (scenario == 0) {
        // Uniform random points
        for (int i = 0; i < N; i++) {
            cows[i].first  = rnd.next(0, 25000);
            cows[i].second = rnd.next(0, 25000);
        }
    } else if (scenario == 1) {
        // Clustered points
        int clusterCount = rnd.next(1, min(3, N));
        vector<pair<int,int>> centers(clusterCount);
        for (int i = 0; i < clusterCount; i++) {
            centers[i].first  = rnd.next(0, 25000);
            centers[i].second = rnd.next(0, 25000);
        }
        int noise = rnd.next(0, 8000);
        for (int i = 0; i < N; i++) {
            int c = rnd.next(0, clusterCount - 1);
            int dx = rnd.next(-noise, noise);
            int dy = rnd.next(-noise, noise);
            int x = centers[c].first + dx;
            int y = centers[c].second + dy;
            // clamp to valid range
            x = max(0, min(25000, x));
            y = max(0, min(25000, y));
            cows[i] = {x, y};
        }
    } else if (scenario == 2) {
        // Horizontal line with small vertical noise
        int y0 = rnd.next(0, 25000);
        for (int i = 0; i < N; i++) {
            int x = rnd.next(0, 25000);
            int dy = rnd.next(-1000, 1000);
            int y = y0 + dy;
            y = max(0, min(25000, y));
            cows[i] = {x, y};
        }
    } else {
        // Vertical line with small horizontal noise
        int x0 = rnd.next(0, 25000);
        for (int i = 0; i < N; i++) {
            int y = rnd.next(0, 25000);
            int dx = rnd.next(-1000, 1000);
            int x = x0 + dx;
            x = max(0, min(25000, x));
            cows[i] = {x, y};
        }
    }

    // Output
    println(N);
    for (auto &p : cows) {
        println(p.first, p.second);
    }
    return 0;
}
