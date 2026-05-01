#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N in three regimes: tiny, small, moderate
    double q = rnd.next();
    int N;
    if (q < 0.2) {
        N = rnd.next(1, 5);
    } else if (q < 0.7) {
        N = rnd.next(6, 15);
    } else {
        N = rnd.next(16, 30);
    }
    // Pattern: 0=random, 1=sorted, 2=reverse sorted, 3=few unique duplicates
    int pattern = rnd.next(0, 3);
    // Choose maxVal to control duplication rate and value range
    double r = rnd.next();
    int maxVal;
    if (r < 0.33) {
        maxVal = rnd.next(1, max(1, N));
    } else if (r < 0.66) {
        maxVal = rnd.next(max(1, N), max(2, N * 3));
    } else {
        maxVal = rnd.next(max(1, N * 3), 10000);
    }
    vector<int> a(N);
    if (pattern == 3) {
        // Few unique values
        int K = rnd.next(1, min(N, 5));
        vector<int> uniq(K);
        for (int i = 0; i < K; i++) {
            uniq[i] = rnd.next(1, maxVal);
        }
        for (int i = 0; i < N; i++) {
            a[i] = rnd.any(uniq);
        }
    } else {
        // Random values
        for (int i = 0; i < N; i++) {
            a[i] = rnd.next(1, maxVal);
        }
    }
    // Apply sorting patterns
    if (pattern == 1) {
        sort(a.begin(), a.end());
    } else if (pattern == 2) {
        sort(a.begin(), a.end(), greater<int>());
    }
    // Output
    println(N);
    for (int v : a) println(v);
    return 0;
}
