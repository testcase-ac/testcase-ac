#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper: choose N with diverse patterns
    double p = rnd.next();
    int N;
    if (p < 0.05) {
        N = 1;
    } else if (p < 0.20) {
        // bias small (min)
        N = rnd.wnext(10, -2) + 1;  // 1..11, biased low
    } else if (p < 0.45) {
        // bias small (max)
        N = rnd.wnext(10, 2) + 1;   // 1..11, biased high
    } else if (p < 0.80) {
        // medium
        N = rnd.next(2, 20);
    } else if (p < 0.95) {
        // large
        N = rnd.next(21, 50);
    } else {
        // extreme
        N = 50;
    }

    // Candidate 1's votes: ensure at least 1
    int v1 = rnd.next(1, 100);
    vector<int> votes(N, 1);
    votes[0] = v1;

    if (N >= 2) {
        int s = rnd.next(0, 5);
        int M = N - 1;
        vector<int> idx(M);
        for (int i = 0; i < M; i++) idx[i] = i + 1;
        shuffle(idx.begin(), idx.end());

        if (s == 0) {
            // All others minimal
            for (int i = 1; i < N; i++)
                votes[i] = 1;
        }
        else if (s == 1) {
            // All others equal to v1
            for (int i = 1; i < N; i++)
                votes[i] = v1;
        }
        else if (s == 2) {
            // Some above, others up to v1
            int k = rnd.next(1, M);
            vector<bool> isHigh(N, false);
            for (int i = 0; i < k; i++) isHigh[idx[i]] = true;
            for (int i = 1; i < N; i++) {
                if (isHigh[i]) {
                    votes[i] = min(v1 + rnd.next(1, 10), 100);
                } else {
                    votes[i] = rnd.next(1, v1);
                }
            }
        }
        else if (s == 3) {
            // All strictly below v1 by up to delta
            int delta = rnd.next(1, 10);
            int hi = max(1, v1 - delta);
            for (int i = 1; i < N; i++)
                votes[i] = rnd.next(1, hi);
        }
        else if (s == 4) {
            // Fully random
            for (int i = 1; i < N; i++)
                votes[i] = rnd.next(1, 100);
        }
        else {
            // Two-peaked: half low (<=v1), half high (>=v1)
            int half = M / 2;
            vector<bool> pickHigh(N, false);
            for (int i = 0; i < half; i++) pickHigh[idx[i]] = true;
            for (int i = 1; i < N; i++) {
                if (pickHigh[i]) votes[i] = rnd.next(v1, 100);
                else             votes[i] = rnd.next(1, v1);
            }
        }
    }

    // Output
    println(N);
    for (int x : votes) println(x);

    return 0;
}
