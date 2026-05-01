#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyperparameter for N: mostly small, sometimes medium or larger (but <=25 for hand-checkable)
    int N;
    int r = rnd.next(0, 9);
    if (r < 5) {
        N = rnd.next(2, 5);
    } else if (r < 8) {
        N = rnd.next(6, 15);
    } else {
        N = rnd.next(16, 25);
    }

    vector<int> a(N+1);
    int mode = rnd.next(0, 3);

    if (mode == 0) {
        // Single chain ending in a cycle
        vector<int> seq(N);
        iota(seq.begin(), seq.end(), 1);
        shuffle(seq.begin(), seq.end());
        for (int i = 0; i < N-1; i++) {
            a[seq[i]] = seq[i+1];
        }
        // last points into the earlier part to form a single cycle
        int rpos = rnd.next(0, N-2);
        a[seq[N-1]] = seq[rpos];
    }
    else if (mode == 1) {
        // Fully random pointers (including possible self loops)
        for (int i = 1; i <= N; i++) {
            a[i] = rnd.next(1, N);
        }
    }
    else if (mode == 2) {
        // Partition into many small cycles
        vector<int> rem(N);
        iota(rem.begin(), rem.end(), 1);
        shuffle(rem.begin(), rem.end());
        int idx = 0;
        while (idx < N) {
            int maxsz = N - idx;
            int sz = rnd.next(1, maxsz);
            // build a cycle of size sz
            for (int j = 0; j < sz-1; j++) {
                a[rem[idx+j]] = rem[idx+j+1];
            }
            a[rem[idx+sz-1]] = rem[idx];
            idx += sz;
        }
    }
    else {
        // All self loops
        for (int i = 1; i <= N; i++) {
            a[i] = i;
        }
    }

    // Output the test case
    println(N);
    for (int i = 1; i <= N; i++) {
        println(a[i]);
    }
    return 0;
}
