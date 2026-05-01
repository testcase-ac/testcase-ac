#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Size hyper-parameter: N from very small to moderate (hand-checkable)
    int N = rnd.next(1, 12);

    // Color count hyper-parameter: variety from 1 up to 1e9
    int cat = rnd.next(0, 3);
    int C;
    if (cat == 0) {
        C = 1;                    // edge: single color only
    } else if (cat == 1) {
        C = rnd.next(2, 3);       // small C
    } else if (cat == 2) {
        C = rnd.next(4, 20);      // moderate C
    } else {
        C = rnd.next(100, 1000000000); // large C
    }

    // Pattern hyper-parameter: generate different segment structures
    int pat = rnd.next(0, 3);
    vector<int> a(N);

    if (pat == 0) {
        // All same
        int v = (C == 1 ? 0 : rnd.next(0, C - 1));
        for (int i = 0; i < N; i++) a[i] = v;
    }
    else if (pat == 1) {
        // Alternating two colors
        if (C == 1) {
            for (int i = 0; i < N; i++) a[i] = 0;
        } else {
            int x = rnd.next(0, C - 1);
            int y = rnd.next(0, C - 1);
            while (y == x) y = rnd.next(0, C - 1);
            for (int i = 0; i < N; i++) {
                a[i] = (i % 2 == 0 ? x : y);
            }
        }
    }
    else if (pat == 2) {
        // A few random segments (2 to min(4,N)), each with distinct color
        if (N == 1) {
            a[0] = 0;
        } else {
            int segs = rnd.next(2, min(4, N));
            vector<int> lens(segs, 1);
            int rem = N - segs;
            // distribute the remaining length
            for (int i = 0; i < rem; i++) {
                int idx = rnd.next(0, segs - 1);
                lens[idx]++;
            }
            int pos = 0, prev = -1;
            for (int k = 0; k < segs; k++) {
                int col;
                if (C == 1) {
                    col = 0;
                } else {
                    do {
                        col = rnd.next(0, C - 1);
                    } while (col == prev);
                }
                for (int t = 0; t < lens[k]; t++) {
                    a[pos++] = col;
                }
                prev = col;
            }
        }
    }
    else {
        // Fully random colors
        for (int i = 0; i < N; i++) {
            a[i] = (C == 1 ? 0 : rnd.next(0, C - 1));
        }
    }

    // Emit the test case
    println(N, C);
    println(a);

    return 0;
}
