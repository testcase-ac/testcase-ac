#include "testlib.h"
#include <algorithm>
#include <vector>
#include <tuple>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose number of villages N: small or medium
    int N;
    if (rnd.next(0, 1) == 0) N = rnd.next(2, 5);
    else N = rnd.next(6, 12);

    // Choose truck capacity C with varied ranges
    int C;
    int r = rnd.next(0, 2);
    if (r == 0) {
        C = rnd.next(1, max(1, N * 5));
    } else if (r == 1) {
        C = rnd.next(N * 5 + 1, max(N * 5 + 1, N * 15));
    } else {
        C = rnd.next(N * 15 + 1, N * 25 + 10);
    }

    // Build all possible (start, end) pairs
    vector<pair<int,int>> pairs;
    for (int i = 1; i <= N; ++i)
        for (int j = i + 1; j <= N; ++j)
            pairs.emplace_back(i, j);
    int maxM = pairs.size();

    // Choose number of shipments M: sparse, medium, or dense
    int M;
    if (maxM >= 4) {
        int sparseMax = max(1, maxM / 4);
        int denseMin = max(1, maxM * 3 / 4);
        if (denseMin >= maxM) denseMin = maxM - 1;
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            M = rnd.next(1, sparseMax);
        } else if (mode == 1) {
            M = rnd.next(sparseMax + 1, denseMin);
        } else {
            M = rnd.next(denseMin + 1, maxM);
        }
    } else {
        M = rnd.next(1, maxM);
    }

    // Sample M unique pairs
    shuffle(pairs.begin(), pairs.end());
    vector<tuple<int,int,int>> shipments;
    for (int i = 0; i < M; ++i) {
        int s = pairs[i].first;
        int e = pairs[i].second;
        int amount;
        // Vary amount: sometimes small, sometimes may exceed capacity
        if (C >= 4 && rnd.next(0, 1) == 0) {
            amount = rnd.next(1, max(1, C / 2));
        } else {
            amount = rnd.next(1, C * 2);
        }
        amount = min(amount, 10000);
        shipments.emplace_back(s, e, amount);
    }

    // Shuffle shipments for extra variability
    shuffle(shipments.begin(), shipments.end());

    // Output the test case
    println(N, C);
    println(M);
    for (auto &t : shipments) {
        int s, e, amt;
        tie(s, e, amt) = t;
        println(s, e, amt);
    }

    return 0;
}
