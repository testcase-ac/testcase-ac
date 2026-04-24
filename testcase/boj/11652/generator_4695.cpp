#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
#include <cstdint>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cards
    int N = rnd.next(1, 10);
    // Number of distinct values
    int C = rnd.next(1, min(N, 5));

    // Range radius for values, keep it small
    int maxValR = min(N * 10, 100);
    int R = rnd.next(0, maxValR);
    R = max(R, C - 1); // ensure enough room for C distinct values

    // Generate C distinct int64_t values in [-R, R]
    set<int64_t> seen;
    vector<int64_t> vals;
    while ((int)vals.size() < C) {
        int64_t x = rnd.next(-R, R);
        if (seen.insert(x).second) {
            vals.push_back(x);
        }
    }

    // Generate weights for each value to bias frequencies
    vector<int> w(C);
    int t = rnd.next(-2, 2);
    int sumW = 0;
    for (int i = 0; i < C; i++) {
        int wi = rnd.wnext(N, t) + 1;
        w[i] = wi;
        sumW += wi;
    }

    // Build the cards list by weighted sampling
    vector<int64_t> cards;
    cards.reserve(N);
    for (int i = 0; i < N; i++) {
        int pick = rnd.next(1, sumW);
        int cum = 0, idx = 0;
        for (; idx < C; idx++) {
            cum += w[idx];
            if (pick <= cum) break;
        }
        if (idx == C) idx = C - 1;
        cards.push_back(vals[idx]);
    }

    // Shuffle the order of cards
    shuffle(cards.begin(), cards.end());

    // Output
    println(N);
    for (auto x : cards) {
        printf("%lld\n", (long long)x);
    }

    return 0;
}
