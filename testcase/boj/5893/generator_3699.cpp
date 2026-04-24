#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: decide length distribution
    int L;
    int r = rnd.next(0, 99);
    if (r < 10) {
        L = 1;                        // Very small
    } else if (r < 40) {
        L = rnd.next(2, 5);           // Small
    } else if (r < 75) {
        L = rnd.next(6, 10);          // Medium
    } else {
        L = rnd.next(11, 15);         // Larger but still hand-checkable
    }

    // Hyper-parameter: choose pattern type
    int type = rnd.next(0, 4);
    string N;

    if (type == 0) {
        // Minimal case
        N = "1";
    } else if (type == 1) {
        // Power of two: 1 followed by zeros
        int zeros = max(1, L) - 1;
        N = "1" + string(zeros, '0');
    } else if (type == 2) {
        // All ones
        N = string(L, '1');
    } else if (type == 3) {
        // Fully random binary with leading 1
        N = "1";
        for (int i = 1; i < L; i++) {
            N += char('0' + rnd.next(0, 1));
        }
    } else {
        // Random with some guaranteed trailing zeros, fallback if L<2
        if (L >= 2) {
            int tz = rnd.next(1, min(L - 1, 5));
            int prefixLen = L - tz;
            N = "1";
            for (int i = 1; i < prefixLen; i++) {
                N += char('0' + rnd.next(0, 1));
            }
            N += string(tz, '0');
        } else {
            // L == 1 fallback to random (which is just "1")
            N = "1";
        }
    }

    println(N);
    return 0;
}
