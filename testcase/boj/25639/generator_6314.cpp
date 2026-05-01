#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: biased to small but sometimes medium
    int tN = rnd.next(-2, 2);
    int N = rnd.wnext(30, tN) + 1;  // N in [1..30]

    // Mode for initial array: 0=random, 1=increasing, 2=decreasing
    int mode = rnd.next(0, 2);
    vector<long long> a(N);
    if (mode == 1) {
        long long cur = rnd.next(-100, 100);
        for (int i = 0; i < N; i++) {
            long long d = rnd.next(0, 5);
            a[i] = cur + d;
            cur = a[i];
        }
    } else if (mode == 2) {
        long long cur = rnd.next(-100, 100);
        for (int i = 0; i < N; i++) {
            long long d = rnd.next(0, 5);
            a[i] = cur - d;
            cur = a[i];
        }
    } else {
        for (int i = 0; i < N; i++) {
            // Mostly small values, occasionally large
            if (rnd.next(0, 3) == 0)
                a[i] = rnd.next((int)-1e9, (int)1e9);
            else
                a[i] = rnd.next(-10, 10);
        }
    }

    // Hyper-parameter for Q: biased similar to N
    int tQ = rnd.next(-2, 2);
    int Q = rnd.wnext(30, tQ) + 1;  // Q in [1..30]

    vector<array<long long,3>> qs(Q);
    int cntType2 = 0;
    for (int i = 0; i < Q; i++) {
        // type1 with 30% prob, type2 with 70%
        bool isType1 = rnd.next(0, 9) < 3;
        if (!isType1) {
            // Query type 2
            int l = rnd.next(1, N);
            int r = rnd.next(l, N);
            qs[i] = {2, l, r};
            cntType2++;
        } else {
            // Query type 1
            int k = rnd.next(1, N);
            long long x;
            if (rnd.next(0, 3) == 0)
                x = rnd.next((int)-1e9, (int)1e9);
            else
                x = rnd.next(-10, 10);
            qs[i] = {1, k, x};
        }
    }
    // Ensure at least one type-2 query
    if (cntType2 == 0) {
        int i = rnd.next(0, Q-1);
        int l = rnd.next(1, N);
        int r = rnd.next(l, N);
        qs[i] = {2, l, r};
    }

    // Output
    println(N);
    println(a);
    println(Q);
    for (auto &qr : qs) {
        println(qr[0], qr[1], qr[2]);
    }
    return 0;
}
