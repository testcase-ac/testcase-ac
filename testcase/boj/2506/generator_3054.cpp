#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose small size
    int N = rnd.next(1, 10);
    vector<int> a(N);

    // Three generation modes for diversity
    int mode = rnd.next(0, 2);
    if (mode == 0) {
        // Independent bits with random density
        double p = rnd.next(0.0, 1.0);
        for (int i = 0; i < N; i++)
            a[i] = (rnd.next() < p) ? 1 : 0;
    } else if (mode == 1) {
        // Alternating blocks of 1s and 0s
        int cur = rnd.next(0, 1);
        int idx = 0;
        while (idx < N) {
            int maxLen = N - idx;
            int len;
            // Occasionally long runs, sometimes short
            if (rnd.next(0, 1))
                len = rnd.next(1, maxLen);
            else
                len = rnd.next(1, min(maxLen, 3));
            for (int j = 0; j < len && idx < N; j++)
                a[idx++] = cur;
            cur ^= 1;
        }
    } else {
        // All same bits
        int v = rnd.next(0, 1);
        for (int i = 0; i < N; i++)
            a[i] = v;
    }

    // Output
    println(N);
    println(a);

    return 0;
}
