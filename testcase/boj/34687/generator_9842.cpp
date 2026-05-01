#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N = 1, M = 1;
    int type = rnd.next(1, 7);

    if (type == 1) {
        // Small readable values
        N = rnd.next(1, 30);
        M = rnd.next(1, 30);
    } else if (type == 2) {
        // Full range random
        N = rnd.next(1, 1000);
        M = rnd.next(1, 1000);
    } else if (type == 3) {
        // Exactly at the success threshold: M = ceil(0.81 * N) (should be "yaho")
        N = rnd.next(2, 1000);
        int ceilThreshold = (81 * N + 99) / 100;
        M = ceilThreshold; // Always between 2 and 810 for N>=2
    } else if (type == 4) {
        // Just below the threshold: M = ceil(0.81 * N) - 1 (should be "no")
        N = rnd.next(2, 1000);
        int ceilThreshold = (81 * N + 99) / 100;
        M = ceilThreshold - 1;
        if (M < 1) M = 1;
    } else if (type == 5) {
        // Integer-division trap:
        // M = floor(0.81 * N), but real condition uses 0.81*N.
        // Correct answer: "no", but buggy code using N*81/100 compared to M says "yaho".
        do {
            N = rnd.next(2, 1000);
        } while ((81 * N) % 100 == 0); // Avoid exact multiples; need fractional part
        int floorThreshold = (81 * N) / 100;
        if (floorThreshold < 1) floorThreshold = 1;
        M = floorThreshold;
    } else if (type == 6) {
        // Extreme ends of range
        N = rnd.any(vector<int>{1, 2, 3, 999, 1000});
        M = rnd.any(vector<int>{1, 2, 3, 999, 1000});
    } else if (type == 7) {
        // Explicit M > N (clear success) or very small M (clear failure)
        N = rnd.next(1, 1000);
        if (rnd.next(0, 1) == 0) {
            // Clear success: M well above threshold and possibly > N
            int minGood = (81 * N + 99) / 100;
            int hi = min(1000, max(minGood + 100, minGood)); // keep within bounds
            M = rnd.next(minGood, hi);
        } else {
            // Clear failure: M much smaller than N
            int hi = max(1, N / 3);
            M = rnd.next(1, hi);
        }
    }

    println(N, M);
    return 0;
}
