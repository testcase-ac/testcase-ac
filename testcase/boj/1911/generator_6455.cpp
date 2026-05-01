#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of puddles
    int N = rnd.next(1, 15);
    // Hyper-parameters for puddle generation
    long long maxLen = rnd.next(1, 20);
    long long gapMax = rnd.next(0, 20);
    // Build non-overlapping puddles
    vector<pair<long long, long long>> puddles;
    long long cur = rnd.next(0LL, 10LL);
    long long maxP = 0;
    for (int i = 0; i < N; i++) {
        long long len = rnd.next(1LL, maxLen);
        long long gap = rnd.next(0LL, gapMax);
        long long s = cur + gap;
        long long e = s + len;
        puddles.emplace_back(s, e);
        cur = e;
        maxP = max(maxP, len);
    }
    // Total span of all puddles
    long long firstStart = puddles.front().first;
    long long totalSpan = cur - firstStart;
    // Choose board length L with three modes
    int mode = rnd.next(0, 2);
    long long L;
    if (mode == 0) {
        // Small boards
        L = rnd.next(1LL, maxP);
    } else if (mode == 1) {
        // Medium boards
        if (totalSpan >= maxP + 1LL)
            L = rnd.next(maxP + 1LL, totalSpan);
        else
            L = maxP;
    } else {
        // Large boards
        L = rnd.next(totalSpan + 1LL, totalSpan + 10LL);
    }
    // Shuffle order to avoid sorted input
    shuffle(puddles.begin(), puddles.end());
    // Output
    println(N, L);
    for (auto &p : puddles) {
        println(p.first, p.second);
    }
    return 0;
}
