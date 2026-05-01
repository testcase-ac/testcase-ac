#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // N biased towards small but up to 30
    int N = rnd.wnext(30, -1) + 1;
    vector<int> a(N);
    // Choose a pattern type for diversity
    int type = rnd.next(0, 4);
    if (type == 0) {
        // all equal
        int x = rnd.next(1, 10);
        for (int i = 0; i < N; i++) a[i] = x;
    } else if (type == 1) {
        // strictly increasing unique
        for (int i = 0; i < N; i++) a[i] = i + 1;
    } else if (type == 2) {
        // random unique from a larger pool
        int maxv = rnd.next(N, N * 3 + 1);
        vector<int> pool(maxv);
        for (int i = 0; i < maxv; i++) pool[i] = i + 1;
        shuffle(pool.begin(), pool.end());
        for (int i = 0; i < N; i++) a[i] = pool[i];
    } else if (type == 3) {
        // random within small range to force duplicates
        int range = rnd.next(1, max(1, N / 2));
        for (int i = 0; i < N; i++) a[i] = rnd.next(1, range);
    } else {
        // blocks of repeats
        int i = 0;
        while (i < N) {
            int len = rnd.next(1, max(1, N / 5));
            int val = rnd.next(1, max(1, N));
            for (int k = 0; k < len && i < N; k++, i++) {
                a[i] = val;
            }
        }
    }
    // Output
    println(N);
    println(a);
    return 0;
}
