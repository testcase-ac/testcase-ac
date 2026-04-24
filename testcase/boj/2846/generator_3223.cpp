#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Small size for hand checking
    int N = rnd.next(1, 10);
    vector<int> p(N);

    if (N == 1) {
        // Single measurement
        p[0] = rnd.next(1, 20);
    } else {
        // Choose a mode for diversity
        int mode = rnd.next(0, 99);
        if (mode < 25) {
            // Pure increasing
            p[0] = rnd.next(1, 20);
            for (int i = 1; i < N; ++i) {
                int inc = rnd.next(1, 5);
                p[i] = p[i-1] + inc;
            }
        } else if (mode < 50) {
            // Pure decreasing
            p[0] = rnd.next(1, 20);
            for (int i = 1; i < N; ++i) {
                int dec = rnd.next(1, 5);
                p[i] = p[i-1] - dec;
                if (p[i] < 1) p[i] = 1;
            }
        } else if (mode < 75) {
            // Completely random with plateaus
            for (int i = 0; i < N; ++i) {
                p[i] = rnd.next(1, 20);
            }
        } else {
            // Piecewise segments of up/down/flat
            int segs = rnd.next(2, min(N, 5));
            vector<int> seglen(segs, 1);
            int rem = N - segs;
            // Distribute the remaining length
            for (int i = 0; i < rem; ++i) {
                int idx = rnd.next(0, segs - 1);
                seglen[idx]++;
            }
            int cur = rnd.next(1, 20);
            int pos = 0;
            for (int s = 0; s < segs; ++s) {
                int type = rnd.next(0, 2); // 0=increase, 1=decrease, 2=flat
                for (int j = 0; j < seglen[s]; ++j) {
                    p[pos++] = cur;
                    if (type == 0) {
                        cur += rnd.next(1, 5);
                    } else if (type == 1) {
                        cur -= rnd.next(1, 5);
                        if (cur < 1) cur = 1;
                    }
                    // flat: cur unchanged
                }
            }
        }
    }

    // Output
    println(N);
    println(p);

    return 0;
}
