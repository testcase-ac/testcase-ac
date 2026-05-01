#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of bars
    int N = rnd.next(1, 20);
    vector<int> a(N);
    // Choose a pattern for heights
    int pattern = rnd.next(0, 4);
    if (pattern == 0) {
        // Fully random
        for (int i = 0; i < N; i++) a[i] = rnd.next(1, N);
    } else if (pattern == 1) {
        // Strictly increasing
        for (int i = 0; i < N; i++) a[i] = i + 1;
    } else if (pattern == 2) {
        // Strictly decreasing
        for (int i = 0; i < N; i++) a[i] = N - i;
    } else if (pattern == 3) {
        // Constant
        int v = rnd.next(1, N);
        for (int i = 0; i < N; i++) a[i] = v;
    } else {
        // Few large plateaus
        int k = rnd.next(1, min(N, 5));
        int used = 0;
        for (int j = 0; j < k; j++) {
            int partsLeft = k - j;
            int rem = N - used;
            int sz = (j + 1 < k ? rnd.next(1, rem - (partsLeft - 1)) : rem);
            int v = rnd.next(1, N);
            for (int t = 0; t < sz; t++) a[used++] = v;
        }
    }
    // Small random noise
    for (int i = 0; i < N; i++) {
        if (rnd.next() < 0.1) a[i] = rnd.next(1, N);
    }
    // Number of queries
    int Q = rnd.next(1, min<int>(N * (N + 1) / 2, 20));
    vector<pair<int,int>> qs;
    for (int i = 0; i < Q; i++) {
        if (i > 0 && rnd.next() < 0.2) {
            // repeat a previous query
            qs.push_back(rnd.any(qs));
        } else {
            int raw, len;
            if (rnd.next() < 0.5) {
                // bias small segments
                raw = rnd.wnext(N, -1);
            } else {
                // bias large segments
                raw = rnd.wnext(N, 1);
            }
            len = raw + 1;
            if (len < 1) len = 1;
            if (len > N) len = N;
            int l = rnd.next(1, N - len + 1);
            int r = l + len - 1;
            qs.emplace_back(l, r);
        }
    }
    shuffle(qs.begin(), qs.end());
    // Output
    println(N);
    println(a);
    println((int)qs.size());
    for (auto &qr : qs) println(qr.first, qr.second);
    return 0;
}
