#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a small grid size for coordinates
    int maxC = rnd.next(5, 20);
    int totalPoints = (maxC + 1) * (maxC + 1);

    // Number of grass patches
    int N = rnd.next(1, min(totalPoints, 20));

    // Build all possible grid points and shuffle to pick distinct ones
    vector<pair<int,int>> coords;
    coords.reserve(totalPoints);
    for (int x = 0; x <= maxC; ++x)
        for (int y = 0; y <= maxC; ++y)
            coords.emplace_back(x, y);
    shuffle(coords.begin(), coords.end());
    coords.resize(N);

    // Hyper-parameter for K: ensure 1 <= K <= 2*maxC
    int maxDist = 2 * maxC;
    int caseK = rnd.next(0, 3);
    int K;
    if (caseK == 0) {
        // Minimal range
        K = 1;
    } else if (caseK == 1) {
        // Small range
        K = rnd.next(1, min(5, maxDist));
    } else if (caseK == 2) {
        // Medium range
        int lo = max(1, maxDist / 4);
        int hi = max(1, maxDist / 2);
        K = rnd.next(lo, hi);
    } else {
        // Large range
        int lo = max(1, maxDist - 5);
        K = rnd.next(lo, maxDist);
    }

    // Output header
    println(N, K);
    // Output each patch: g_i, x_i, y_i
    for (int i = 0; i < N; ++i) {
        int g;
        // Diverse grass amounts: small or heavy
        if (rnd.next(0, 1) == 0) {
            g = rnd.next(1, 10);
        } else {
            g = rnd.next(1000, 10000);
        }
        println(g, coords[i].first, coords[i].second);
    }

    return 0;
}
