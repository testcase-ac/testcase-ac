#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N with some variability
    int modeN = rnd.next(0, 4);
    int N;
    if (modeN == 0) {
        N = 1;
    } else if (modeN == 1) {
        N = 2;
    } else if (modeN == 2) {
        N = rnd.next(3, 10);
    } else if (modeN == 3) {
        // medium biased towards upper
        N = rnd.wnext(20, 1) + 1; // roughly 1..21, bias to bigger
    } else {
        // occasional larger case
        N = rnd.next(50, 100);
    }

    // Generate non-decreasing array a of size N
    vector<long long> a(N);
    int type = rnd.next(0, 3);
    if (type == 0) {
        // all equal
        long long v = rnd.next(1, 5);
        for (int i = 0; i < N; i++) a[i] = v;
    } else if (type == 1) {
        // strictly increasing
        a[0] = rnd.next(1, 10);
        for (int i = 1; i < N; i++) {
            a[i] = a[i - 1] + rnd.next(1, 3);
        }
    } else if (type == 2) {
        // non-decreasing with occasional duplicates
        a[0] = rnd.next(1, 5);
        for (int i = 1; i < N; i++) {
            if (rnd.next(0, 1) == 0) {
                a[i] = a[i - 1];  // duplicate
            } else {
                a[i] = a[i - 1] + rnd.next(0, 3);
            }
        }
    } else {
        // pick from a small set then sort
        int K = rnd.next(1, min(N, 5));
        vector<long long> vals(K);
        vals[0] = rnd.next(1, 5);
        for (int i = 1; i < K; i++) {
            vals[i] = vals[i - 1] + rnd.next(0, 5);
        }
        for (int i = 0; i < N; i++) {
            a[i] = rnd.any(vals);
        }
        sort(a.begin(), a.end());
    }

    // Cap values to <= 1e9
    for (int i = 0; i < N; i++) {
        if (a[i] > 1000000000) a[i] = 1000000000;
    }

    // Output
    println(N);
    println(a);
    return 0;
}
