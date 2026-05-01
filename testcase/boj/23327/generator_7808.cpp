#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter for N: small, medium, large
    double tp = rnd.next();
    int N;
    if (tp < 0.2) {
        N = rnd.next(2, 5);
    } else if (tp < 0.7) {
        N = rnd.next(6, 12);
    } else {
        N = rnd.next(13, 20);
    }

    // Compute maximum reasonable Q
    int maxQ = min(N * (N - 1) / 2, 50);
    // Hyper-parameter for Q: few, moderate, max
    double tq = rnd.next();
    int small_hi = min(N, maxQ);
    int Q;
    if (tq < 0.2) {
        Q = rnd.next(1, small_hi);
    } else if (tq < 0.7) {
        Q = rnd.next(small_hi, maxQ);
    } else {
        Q = maxQ;
    }

    // Generate popularity array a[1..N] with various patterns
    vector<int> a(N);
    int pd = rnd.next(0, 4);
    if (pd == 0) {
        // completely random
        for (int i = 0; i < N; i++) a[i] = rnd.next(1, 1000);
    } else if (pd == 1) {
        // all equal
        int v = rnd.next(1, 1000);
        for (int &x : a) x = v;
    } else if (pd == 2) {
        // non-decreasing
        a[0] = rnd.next(1, 1000);
        for (int i = 1; i < N; i++) {
            a[i] = min(1000, a[i-1] + rnd.next(0, 5));
        }
    } else if (pd == 3) {
        // non-increasing
        a[N-1] = rnd.next(1, 1000);
        for (int i = N-2; i >= 0; i--) {
            a[i] = min(1000, a[i+1] + rnd.next(0, 5));
        }
    } else {
        // small range
        int low = rnd.next(1, 900);
        int high = rnd.next(low, low + 100);
        for (int i = 0; i < N; i++) a[i] = rnd.next(low, high);
    }

    // Generate Q queries with diverse interval lengths
    vector<pair<int,int>> qs;
    qs.reserve(Q);
    for (int i = 0; i < Q; i++) {
        double t = rnd.next();
        int l, r, len;
        if (t < 0.2) {
            // small length
            len = rnd.next(1, min(5, N-1));
            l = rnd.next(1, N - len);
            r = l + len;
        } else if (t < 0.35) {
            // adjacent pairs
            l = rnd.next(1, N - 1);
            r = l + 1;
        } else if (t < 0.55 && N > 10) {
            // medium length
            len = rnd.next(6, min(10, N-1));
            l = rnd.next(1, N - len);
            r = l + len;
        } else if (t < 0.75 && N > 6) {
            // large length
            len = rnd.next(max(1, N - 5), N - 1);
            l = rnd.next(1, N - len);
            r = l + len;
        } else {
            // fully random
            l = rnd.next(1, N - 1);
            r = rnd.next(l + 1, N);
        }
        qs.emplace_back(l, r);
    }
    shuffle(qs.begin(), qs.end());

    // Output
    println(N, Q);
    println(a);
    for (auto &qr : qs) {
        println(qr.first, qr.second);
    }

    return 0;
}
