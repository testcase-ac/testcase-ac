#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small sizes for hand-checkable cases
    int N = rnd.next(1, 10);
    int K = rnd.next(1, 10);
    vector<int> f(N+1);

    // Four modes to diversify f_i distribution
    int mode = rnd.next(0, 3);
    if (mode == 0) {
        // Independent mapping with some fixed points
        int pi = rnd.next(0, 100);
        double p_self = pi / 100.0;
        for (int i = 1; i <= N; ++i) {
            if (rnd.next() < p_self || N == 1) {
                f[i] = i;
            } else {
                int x = rnd.next(1, N-1);
                if (x >= i) x++;
                f[i] = x;
            }
        }
    } else if (mode == 1) {
        // Chain emphasis: point to previous index often
        int pi = rnd.next(0, 100);
        double p_chain = pi / 100.0;
        f[1] = 1;
        for (int i = 2; i <= N; ++i) {
            if (rnd.next() < p_chain) {
                f[i] = i-1;
            } else {
                int x = rnd.next(1, N-1);
                if (x >= i) x++;
                f[i] = x;
            }
        }
    } else if (mode == 2) {
        // Single big cycle, then sprinkle some fixed points
        vector<int> perm(N);
        iota(perm.begin(), perm.end(), 1);
        shuffle(perm.begin(), perm.end());
        for (int i = 0; i < N; ++i) {
            int u = perm[i], v = perm[(i+1)%N];
            f[u] = v;
        }
        int fixes = rnd.next(0, N);
        for (int t = 0; t < fixes; ++t) {
            int i = rnd.next(1, N);
            f[i] = i;
        }
    } else {
        // Hub-and-spoke: many point to one hub
        int hub = rnd.next(1, N);
        int pi = rnd.next(0, 100);
        double p_hub = pi / 100.0;
        for (int i = 1; i <= N; ++i) {
            if (i == hub) {
                f[i] = i;
            } else if (rnd.next() < p_hub) {
                f[i] = hub;
            } else {
                int x = rnd.next(1, N-1);
                if (x >= i) x++;
                f[i] = x;
            }
        }
    }

    // Output
    println(N, K);
    for (int i = 1; i <= N; ++i) {
        printf("%d%c", f[i], (i == N ? '\n' : ' '));
    }
    return 0;
}
