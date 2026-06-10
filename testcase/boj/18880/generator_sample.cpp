#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 40);
    string stalls(n, '0');

    if (mode == 0) {
        // All-empty barns are allowed by the local validator.
    } else if (mode == 1) {
        int left = rnd.next(0, n - 1);
        int right = rnd.next(left, n - 1);
        stalls[left] = '1';
        stalls[right] = '1';
    } else if (mode == 2) {
        for (int i = rnd.next(0, 1); i < n; i += 2) {
            stalls[i] = '1';
        }
    } else if (mode == 3) {
        int blockCount = rnd.next(1, min(4, n));
        for (int b = 0; b < blockCount; ++b) {
            int start = rnd.next(0, n - 1);
            int len = rnd.next(1, min(5, n - start));
            for (int i = start; i < start + len; ++i) {
                stalls[i] = '1';
            }
        }
    } else if (mode == 4) {
        int gapStart = rnd.next(0, n - 2);
        int gapLen = rnd.next(2, n - gapStart);
        for (int i = 0; i < n; ++i) {
            stalls[i] = '1';
        }
        for (int i = gapStart; i < gapStart + gapLen; ++i) {
            stalls[i] = '0';
        }
    } else if (mode == 5) {
        double p = rnd.next(0.15, 0.85);
        for (int i = 0; i < n; ++i) {
            if (rnd.next() < p) {
                stalls[i] = '1';
            }
        }
    } else {
        int first = rnd.next(0, n - 1);
        int second = rnd.next(0, n - 1);
        stalls[first] = '1';
        stalls[second] = '1';
        if (rnd.next(0, 1)) {
            reverse(stalls.begin(), stalls.end());
        }
    }

    while (count(stalls.begin(), stalls.end(), '0') < 2) {
        stalls[rnd.next(0, n - 1)] = '0';
    }

    println(n);
    println(stalls);

    return 0;
}
