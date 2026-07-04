#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxC = (1LL << 30) - 1;
    const long long maxWeight = (1LL << 31) - 1;

    int mode = rnd.next(0, 5);
    int n = 1;
    vector<long long> weights;

    if (mode == 0) {
        n = 1;
        weights.push_back(rnd.next(1, 25));
    } else if (mode == 1) {
        n = 2;
        long long a = rnd.next(1, 100);
        long long b = rnd.next(a, a + 200);
        weights = {a, b};
    } else if (mode == 2) {
        n = rnd.next(3, 14);
        weights = {rnd.next(1, 5), rnd.next(1, 8)};
        if (weights[0] > weights[1]) swap(weights[0], weights[1]);
        for (int i = 2; i < n; ++i) {
            long long base = weights[i - 1] + weights[i - 2];
            weights.push_back(base + rnd.next(0, 3));
        }
    } else if (mode == 3) {
        n = rnd.next(3, 12);
        weights = {rnd.next(1, 20), rnd.next(20, 80)};
        if (weights[0] > weights[1]) swap(weights[0], weights[1]);
        for (int i = 2; i < n; ++i) {
            long long base = weights[i - 1] + weights[i - 2];
            long long extra = rnd.next(0, 4) * weights[i - 1] + rnd.next(0, 50);
            weights.push_back(base + extra);
        }
    } else if (mode == 4) {
        n = rnd.next(8, 25);
        weights = {1, 1};
        for (int i = 2; i < n; ++i) {
            weights.push_back(weights[i - 1] + weights[i - 2]);
        }
    } else {
        n = rnd.next(3, 8);
        long long first = rnd.next(1, 1000);
        long long second = rnd.next(first, first + 1000);
        weights = {first, second};
        for (int i = 2; i < n; ++i) {
            long long base = weights[i - 1] + weights[i - 2];
            long long room = maxWeight - base;
            long long extra = rnd.next(0LL, min(room, 100000000LL));
            weights.push_back(base + extra);
        }
        weights.back() = rnd.next(max(maxWeight / 2, weights[n - 2] + weights[n - 3]), maxWeight);
    }

    long long total = 0;
    for (long long w : weights) {
        total = min(maxC, total + min(w, maxC));
    }

    long long c;
    int capMode = rnd.next(0, 4);
    if (capMode == 0) {
        c = rnd.next(1LL, min(maxC, max(1LL, weights[0])));
    } else if (capMode == 1) {
        c = rnd.next(1LL, max(1LL, min(maxC, total)));
    } else if (capMode == 2) {
        c = min(maxC, rnd.any(weights));
    } else if (capMode == 3) {
        long long pivot = rnd.any(weights);
        c = min(maxC, pivot + rnd.next(0LL, min(50LL, maxC - min(maxC, pivot))));
    } else {
        c = maxC;
    }

    println(n, c);
    for (long long w : weights) {
        println(w);
    }

    return 0;
}
