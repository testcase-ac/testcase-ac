#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of items
    int N = rnd.next(1, 12);
    vector<pair<int,int>> items;
    items.reserve(N);
    // Decide a mode for weight bias: small weights or large weights
    bool smallMode = rnd.next(0,1);
    for (int i = 0; i < N; i++) {
        int w;
        // 1/4 purely random, otherwise biased by mode
        if (rnd.next(0,3) == 0) {
            w = rnd.next(1, 100000);
        } else if (smallMode) {
            // bias towards small weights
            w = rnd.wnext(20, -1) + 1; // range [1,20]
        } else {
            // bias towards large weights
            w = rnd.wnext(100000, 1); // range [0,100000), but zero is rare
            if (w == 0) w = 1;
        }
        // Value: sometimes zero to test skipping worthless items
        int v;
        if (rnd.next(0,4) == 0) {
            v = 0;
        } else {
            v = rnd.next(1, 1000);
        }
        items.emplace_back(w, v);
    }
    // Shuffle item order
    shuffle(items.begin(), items.end());
    // Compute sum of weights, cap for K choice
    long long sumW = 0;
    for (auto &p : items) sumW += p.first;
    const int MAXK = 100000;
    int sumWcap = int(min<long long>(sumW, MAXK));
    // Choose capacity K with various patterns
    int K;
    int caseK = rnd.next(0, 4);
    if (caseK == 0) {
        // Minimal capacity
        K = 1;
    } else if (caseK == 1) {
        // Exactly sum of weights (or max)
        K = sumWcap;
    } else if (caseK == 2) {
        // Random small capacity up to sumWcap
        K = rnd.next(1, sumWcap);
    } else if (caseK == 3) {
        // Slightly above sumWcap to allow all items
        if (sumWcap < MAXK) {
            K = rnd.next(sumWcap + 1, MAXK);
        } else {
            K = MAXK;
        }
    } else {
        // Bias towards small capacities
        K = rnd.wnext(sumWcap, -1) + 1;
        if (K > MAXK) K = MAXK;
    }
    // Output
    println(N, K);
    for (auto &p : items) {
        println(p.first, p.second);
    }
    return 0;
}
