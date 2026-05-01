#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N with bias: small, medium, large
    int N;
    double r = rnd.next();
    if (r < 0.2) {
        N = rnd.next(1, 5);
    } else if (r < 0.6) {
        N = rnd.next(6, 20);
    } else {
        N = rnd.next(21, 40);
    }

    // Choose pattern type
    int type = rnd.next(0, 4);
    vector<long long> h(N);

    if (type == 0) {
        // Completely random heights
        int Hmax = rnd.next(10, 1000);
        for (int i = 0; i < N; i++) {
            h[i] = rnd.next(1, Hmax);
        }
    } else if (type == 1) {
        // Strictly increasing
        long long cur = rnd.next(1, 10);
        for (int i = 0; i < N; i++) {
            cur += rnd.next(1, 50);
            h[i] = cur;
        }
    } else if (type == 2) {
        // Strictly decreasing
        long long cur = rnd.next(N * 50, N * 50 + 1000);
        for (int i = 0; i < N; i++) {
            cur -= rnd.next(1, 50);
            if (cur < 1) cur = 1;
            h[i] = cur;
        }
    } else if (type == 3) {
        // Mountain: increase then decrease
        int p = rnd.next(1, N);
        vector<long long> A(p), B(max(0, N - p));
        long long cur = rnd.next(1, 20);
        for (int i = 0; i < p; i++) {
            cur += rnd.next(1, 30);
            A[i] = cur;
        }
        long long cur2 = A.back();
        for (int i = 0; i < (int)B.size(); i++) {
            cur2 -= rnd.next(1, 30);
            if (cur2 < 1) cur2 = 1;
            B[i] = cur2;
        }
        for (int i = 0; i < p; i++) h[i] = A[i];
        for (int i = p; i < N; i++) h[i] = B[i - p];
    } else {
        // Flat segments
        int idx = 0;
        while (idx < N) {
            int rem = N - idx;
            int maxLen = max(1, N / 5);
            int len = rnd.next(1, maxLen);
            if (len > rem) len = rem;
            long long val = rnd.next(1, 1000);
            for (int j = 0; j < len; j++) {
                h[idx++] = val;
            }
        }
    }

    // Optionally shuffle a bit to introduce local swaps, to combine patterns
    if (rnd.next() < 0.1 && N > 1) {
        int i = rnd.next(0, N - 2);
        swap(h[i], h[i+1]);
    }

    // Output
    println(N);
    for (auto x : h) println(x);

    return 0;
}
