#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of classes
    int N = rnd.next(1, 20);
    // Maximum time bound for manual verifiability
    int T_max = rnd.any(vector<int>{10, 30, 100});
    // Choose a pattern to expose different edge cases
    int pattern = rnd.next(0, 4);
    vector<pair<int,int>> intervals;
    if (pattern == 0) {
        // Pure random intervals
        for (int i = 0; i < N; i++) {
            int S = rnd.next(0, T_max - 1);
            int T = rnd.next(S + 1, T_max);
            intervals.emplace_back(S, T);
        }
    } else if (pattern == 1) {
        // All intervals overlap at some common point
        int L = rnd.next(0, T_max - 2);
        int R = rnd.next(L + 1, T_max);
        for (int i = 0; i < N; i++) {
            int S = rnd.next(0, L);
            int T = rnd.next(R, T_max);
            intervals.emplace_back(S, T);
        }
    } else if (pattern == 2) {
        // Chain of non-overlapping intervals
        int current = 0;
        for (int i = 0; i < N; i++) {
            int rem = N - i - 1;
            int maxLen = max(1, T_max - current - rem);
            int len = rnd.next(1, maxLen);
            int S = current;
            int T = current + len;
            intervals.emplace_back(S, T);
            current = T;
        }
    } else if (pattern == 3) {
        // Some duplicates and some random
        int K = rnd.next(1, N);
        int S0 = rnd.next(0, T_max - 1);
        int T0 = rnd.next(S0 + 1, T_max);
        for (int i = 0; i < K; i++)
            intervals.emplace_back(S0, T0);
        for (int i = K; i < N; i++) {
            int S = rnd.next(0, T_max - 1);
            int T = rnd.next(S + 1, T_max);
            intervals.emplace_back(S, T);
        }
    } else {
        // Two-phase: early cluster and late cluster
        int earlyCount = (N > 1 ? rnd.next(1, N - 1) : 1);
        int lateCount = N - earlyCount;
        // Early half in [0, T_max/2]
        for (int i = 0; i < earlyCount; i++) {
            int S = rnd.next(0, T_max/2 - 1);
            int T = rnd.next(S + 1, T_max/2);
            intervals.emplace_back(S, T);
        }
        // Late half in [T_max/2, T_max]
        for (int i = 0; i < lateCount; i++) {
            int S = rnd.next(T_max/2, T_max - 1);
            int T = rnd.next(S + 1, T_max);
            intervals.emplace_back(S, T);
        }
    }
    // Shuffle to randomize order
    shuffle(intervals.begin(), intervals.end());
    // Output
    println(N);
    for (auto &p : intervals) {
        println(p.first, p.second);
    }
    return 0;
}
