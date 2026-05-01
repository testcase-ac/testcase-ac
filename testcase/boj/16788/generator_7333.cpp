#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Size of the archipelago
    int N = rnd.next(1, 20);
    // Maximum height value
    int maxH = rnd.next(0, 50);

    vector<int> A(N);
    // Choose a pattern type for diversity
    int type = rnd.next(0, 3);
    if (type == 0) {
        // Fully random heights
        for (int i = 0; i < N; i++) {
            A[i] = rnd.next(0, maxH);
        }
    } else if (type == 1) {
        // Monotonic increasing or decreasing
        bool inc = rnd.next(0, 1) == 0;
        if (inc) {
            int last = rnd.next(0, maxH);
            for (int i = 0; i < N; i++) {
                A[i] = last;
                int delta = rnd.next(0, maxH / (N + 1) + 1);
                last = min(last + delta, maxH);
            }
        } else {
            int last = rnd.next(0, maxH);
            for (int i = 0; i < N; i++) {
                A[i] = last;
                int delta = rnd.next(0, maxH / (N + 1) + 1);
                last = max(0, last - delta);
            }
        }
    } else if (type == 2) {
        // Single mountain shape
        int p = rnd.next(0, N - 1);
        int peakH = rnd.next(0, maxH);
        int cur = 0;
        for (int i = 0; i <= p; i++) {
            int inc = rnd.next(0, peakH);
            cur = min(cur + inc, peakH);
            A[i] = cur;
        }
        cur = A[p];
        for (int i = p + 1; i < N; i++) {
            int dec = rnd.next(0, peakH);
            cur = max(0, cur - dec);
            A[i] = cur;
        }
    } else {
        // Plateau-heavy: often repeat previous
        for (int i = 0; i < N; i++) {
            if (i > 0 && rnd.next() < 0.3) {
                A[i] = A[i - 1];
            } else {
                A[i] = rnd.next(0, maxH);
            }
        }
    }

    // Ensure not all zero to avoid trivial no-island case
    bool allZero = true;
    for (int x : A) if (x > 0) allZero = false;
    if (allZero) {
        A[rnd.next(0, N - 1)] = 1;
    }

    // Output
    println(N);
    println(A);

    return 0;
}
