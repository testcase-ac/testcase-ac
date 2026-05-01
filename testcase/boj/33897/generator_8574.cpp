#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N (keep small / medium, max 40)
    int szChoice = rnd.next(1, 100);
    int N;
    if (szChoice <= 10)      N = rnd.next(1, 3);    // very small
    else if (szChoice <= 40) N = rnd.next(4, 10);   // small
    else if (szChoice <= 80) N = rnd.next(11, 25);  // medium
    else                     N = rnd.next(26, 40);  // medium-large but still hand-checkable

    int pattern = rnd.next(0, 6); // 7 different patterns: 0..6
    vector<int> a;
    a.reserve(N);

    if (pattern == 0) {
        // Pattern 0: non-decreasing (often strictly) sequence
        int cur = rnd.next(1, 100);
        for (int i = 0; i < N; ++i) {
            a.push_back(cur);
            if (i + 1 < N)
                cur += rnd.next(0, 10); // allow equal or increase
        }
    } else if (pattern == 1) {
        // Pattern 1: strictly decreasing, many short runs
        int start = 100000000; // near upper bound
        for (int i = 0; i < N; ++i) {
            a.push_back(start - i); // strictly decreasing, all >= 1
        }
    } else if (pattern == 2) {
        // Pattern 2: random in small value range (lots of equalities / small fluctuations)
        int maxVal = rnd.next(2, 7);
        for (int i = 0; i < N; ++i) {
            a.push_back(rnd.next(1, maxVal));
        }
    } else if (pattern == 3) {
        // Pattern 3: "stairs" - blocks of non-decreasing values with drops between blocks
        int cur = rnd.next(20, 200);
        int rem = N;
        while (rem > 0) {
            int len = rnd.next(1, min(rem, 7));
            for (int i = 0; i < len; ++i) {
                a.push_back(cur);
                if (i + 1 < len) {
                    cur += rnd.next(0, 5); // inside block non-decreasing
                }
            }
            rem -= len;
            if (rem > 0) {
                int lastVal = a.back();
                int drop = rnd.next(1, 5);
                cur = lastVal - drop; // ensure next block starts lower
                if (cur < 1) cur = 1;
            }
        }
    } else if (pattern == 4) {
        // Pattern 4: alternating high-low values
        int lowBase = rnd.next(1, 20);
        int highBase = lowBase + rnd.next(3, 15);
        for (int i = 0; i < N; ++i) {
            int val;
            if (i % 2 == 0)
                val = highBase + rnd.next(0, 2);
            else
                val = lowBase + rnd.next(0, 2);
            a.push_back(val);
        }
    } else if (pattern == 5) {
        // Pattern 5: descending plateaus (constant blocks with decreasing heights)
        int cur = rnd.next(100, 300);
        int rem = N;
        while (rem > 0) {
            int len = rnd.next(1, min(rem, 6));
            for (int i = 0; i < len; ++i) {
                a.push_back(cur); // plateau
            }
            rem -= len;
            if (rem > 0) {
                int drop = rnd.next(1, 5);
                cur -= drop; // next plateau lower
                if (cur < 1) cur = 1;
            }
        }
    } else if (pattern == 6) {
        // Pattern 6: mixture - random run lengths of non-decreasing segments with drops between
        int curVal = 1000 + 10 * N; // ensure always positive even after many drops
        int rem = N;
        while (rem > 0) {
            int len = rnd.next(1, min(rem, 8));
            for (int i = 0; i < len; ++i) {
                a.push_back(curVal);
                if (i + 1 < len) {
                    curVal += rnd.next(0, 5); // within run non-decreasing
                }
            }
            rem -= len;
            if (rem > 0) {
                int drop = rnd.next(1, 10);
                curVal -= drop; // force a drop -> new run
            }
        }
    }

    // Output
    println(N);
    println(a);

    return 0;
}
