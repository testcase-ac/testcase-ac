#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    long long C;
    vector<long long> w;

    int type = rnd.next(0, 8);

    if (type == 0) {
        // Minimal N = 1 with various C relations
        N = 1;
        int wi = rnd.next(1, 1000000000);
        w.push_back(wi);
        int opt = rnd.next(0, 3);
        if (opt == 0) {
            C = 0;
        } else if (opt == 1) {
            if (wi > 1)
                C = rnd.next(0, wi - 1);
            else
                C = 0;
        } else if (opt == 2) {
            C = wi;
        } else {
            C = rnd.next(wi, 1000000000);
        }
    } else if (type == 1) {
        // Small N, small weights
        N = rnd.next(2, 5);
        long long sumW = 0;
        for (int i = 0; i < N; i++) {
            int wi = rnd.next(1, 20);
            w.push_back(wi);
            sumW += wi;
        }
        int opt = rnd.next(0, 3);
        if (opt == 0) {
            C = rnd.next(0, (int)sumW);
        } else if (opt == 1) {
            int hi = (int)min(20LL, sumW);
            C = rnd.next(0, hi);
        } else if (opt == 2) {
            C = sumW;
        } else {
            long long extra = rnd.next(1, 20);
            long long val = sumW + extra;
            if (val > 1000000000LL) val = 1000000000LL;
            C = val;
        }
    } else if (type == 2) {
        // Large N, tiny weights
        N = rnd.next(20, 30);
        long long sumW = 0;
        for (int i = 0; i < N; i++) {
            int wi = rnd.next(1, 5);
            w.push_back(wi);
            sumW += wi;
        }
        int opt = rnd.next(0, 2);
        if (opt == 0) {
            C = sumW;
        } else if (opt == 1) {
            C = sumW / 2;
        } else {
            int lo = (int)(sumW / 3);
            int hi = (int)(2 * sumW / 3);
            if (hi < lo) hi = lo;
            C = rnd.next(lo, hi);
        }
    } else if (type == 3) {
        // Mostly too-heavy items
        N = rnd.next(5, 15);
        int Cint = rnd.next(0, 50);
        C = Cint;
        for (int i = 0; i < N; i++) {
            int wi;
            if (Cint == 0) {
                wi = rnd.next(1, 50);
            } else {
                if (rnd.next(0, 3) != 0) {
                    wi = Cint + rnd.next(1, 50);
                } else {
                    wi = rnd.next(1, Cint);
                }
            }
            if (wi > 1000000000) wi = 1000000000;
            w.push_back(wi);
        }
    } else if (type == 4) {
        // All equal weights, controlled max count of items
        N = rnd.next(8, 25);
        int wv = rnd.next(1, 20);
        int k = rnd.next(0, N);
        long long base = 1LL * wv * k;
        long long maxC = base + wv - 1;
        if (maxC > 1000000000LL) maxC = 1000000000LL;
        if (base > maxC) base = maxC;
        int Cint = rnd.next((int)base, (int)maxC);
        C = Cint;
        w.assign(N, wv);
    } else if (type == 5) {
        // Mixed small and very large weights, large C
        int Cint = rnd.next(100000000, 1000000000);
        C = Cint;
        N = rnd.next(10, 20);
        for (int i = 0; i < N; i++) {
            int wi;
            if (rnd.next(0, 1) == 0) {
                wi = rnd.next(1, 1000000);
            } else {
                int lo = Cint / 2;
                if (lo < 1) lo = 1;
                int hi = Cint + 100000000;
                if (hi > 1000000000) hi = 1000000000;
                if (hi < lo) hi = lo;
                wi = rnd.next(lo, hi);
            }
            w.push_back(wi);
        }
    } else if (type == 6) {
        // C at maximum, many huge weights
        C = 1000000000;
        N = rnd.next(20, 30);
        for (int i = 0; i < N; i++) {
            int wi;
            if (rnd.next(0, 2) == 0) {
                wi = rnd.next(1, 1000000);
            } else {
                wi = rnd.next(500000000, 1000000000);
            }
            w.push_back(wi);
        }
    } else if (type == 7) {
        // All large weights, C large; few subsets fit
        N = 30;
        int Cint = rnd.next(500000000, 1000000000);
        C = Cint;
        for (int i = 0; i < N; i++) {
            int wi = rnd.next(400000000, 1000000000);
            w.push_back(wi);
        }
    } else {
        // type == 8: all ones, varying C (combinatorial counts)
        N = 30;
        C = rnd.next(0, 30);
        w.assign(N, 1);
    }

    println(N, C);
    for (int i = 0; i < N; i++) {
        if (i) printf(" ");
        printf("%lld", w[i]);
    }
    printf("\n");

    return 0;
}
