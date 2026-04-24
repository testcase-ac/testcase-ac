#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of trophies
    int N = rnd.next(1, 10);
    vector<int> h(N);

    if (N == 1) {
        // Single trophy, just random height
        h[0] = rnd.next(1, 100);
    } else {
        // Choose a pattern for diversity
        int pattern = rnd.next(0, 4);
        if (pattern == 0) {
            // Pure random heights
            for (int i = 0; i < N; i++) {
                h[i] = rnd.next(1, 100);
            }
        } else if (pattern == 1) {
            // Non-decreasing (increasing) sequence
            h[0] = rnd.next(1, 10);
            for (int i = 1; i < N; i++) {
                h[i] = h[i-1] + rnd.next(0, 10);
                if (h[i] > 100) h[i] = 100;
            }
        } else if (pattern == 2) {
            // Non-increasing (decreasing) sequence
            h[0] = rnd.next(1, 100);
            for (int i = 1; i < N; i++) {
                h[i] = max(1, h[i-1] - rnd.next(0, 10));
            }
        } else if (pattern == 3) {
            // One big peak somewhere
            int peak = rnd.next(0, N - 1);
            for (int i = 0; i < N; i++) {
                h[i] = rnd.next(1, 50);
            }
            h[peak] = rnd.next(51, 100);
        } else {
            // Plateau then random jump
            int split = rnd.next(1, N - 1);
            int val = rnd.next(1, 100);
            for (int i = 0; i < split; i++) {
                h[i] = val;
            }
            for (int i = split; i < N; i++) {
                h[i] = rnd.next(1, 100);
            }
        }
    }

    // Output format
    println(N);
    for (int x : h) println(x);

    return 0;
}
