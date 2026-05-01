#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with slight bias towards smaller sizes
    int diceN = rnd.next(1, 100);
    int N;
    if (diceN <= 50)      N = rnd.next(3, 6);
    else if (diceN <= 85) N = rnd.next(7, 10);
    else                  N = rnd.next(11, 15);

    // Choose X with varied ranges
    int diceX = rnd.next(1, 100);
    int X;
    if (diceX <= 40)       X = rnd.next(1, 5);
    else if (diceX <= 80)  X = rnd.next(6, 20);
    else if (diceX <= 95)  X = rnd.next(21, 50);
    else                   X = rnd.next(51, 100);

    vector<int> T(N);
    int mode = rnd.next(0, 2); // 0,1,2

    // Precompute first-lap heights
    vector<int> H(N);
    for (int i = 0; i < N; ++i) {
        H[i] = X + i; // player i+1 height in first lap
    }

    // Generate base T array with different shapes
    for (int i = 0; i < N; ++i) {
        int h = H[i];
        int lo, hi;
        if (mode == 0) {
            // Completely random
            lo = 1;
            hi = 200;
        } else if (mode == 1) {
            // Around their first-lap height, more often safe
            lo = max(1, h - 5);
            hi = min(200, h + 50);
        } else { // mode == 2
            // Often relatively low, closer to or below height
            lo = 1;
            hi = min(200, h + 5);
        }
        if (lo > hi) lo = hi; // just in case
        T[i] = rnd.next(lo, hi);
    }

    // Ensure that at least one player loses on the first lap,
    // i.e., there exists i with H[i] > T[i].
    vector<int> loseCandidates;
    for (int i = 0; i < N; ++i) {
        if (H[i] > T[i]) loseCandidates.push_back(i);
    }

    if (loseCandidates.empty()) {
        // Force at least one loser in first lap.
        // Choose among players with H[i] >= 2 so that we can set T[i] < H[i].
        vector<int> canForce;
        for (int i = 0; i < N; ++i) {
            if (H[i] >= 2) canForce.push_back(i);
        }
        // There is always at least one such player since N >= 3.
        int idx = rnd.any(canForce);
        int h = H[idx];
        // Set T[idx] in [1, h-1] so that H[idx] > T[idx]
        T[idx] = rnd.next(1, h - 1);
    }

    println(N, X);
    println(T);

    return 0;
}
