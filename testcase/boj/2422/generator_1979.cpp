#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Generate N in the small range [3, 10] to keep the testcase verifiable.
    int N = rnd.next(3, 10);
    // Maximum number of distinct pairings is C(N, 2)
    int maxPairs = N * (N - 1) / 2;
    // To add variety, we randomly choose M between 0 and maxPairs.
    int M = rnd.next(0, maxPairs);

    vector<pair<int, int>> pairs;
    // Hyperparameter: swap_prob randomly chosen from [0.0, 1.0]
    double swap_prob = rnd.next(0.0, 1.0);
    for (int i = 1; i <= N; i++) {
        for (int j = i + 1; j <= N; j++) {
            pairs.push_back({i, j});
            if (rnd.next(0.0, 1.0) < swap_prob) {
                swap(pairs.back().first, pairs.back().second);
            }
        }
    }
    // Shuffle all possible pairs to choose a random subset of M impossible pairings.
    shuffle(pairs.begin(), pairs.end());
    
    println(N, M);
    for (int i = 0; i < M; i++) {
        println(pairs[i].first, pairs[i].second);
    }
    return 0;
}
