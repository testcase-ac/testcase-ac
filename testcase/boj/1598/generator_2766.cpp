#include "testlib.h"
#include <vector>
#include <string>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: maximum number
    int maxN = rnd.next(4, 100);
    // Hyper-parameter: pattern for diversity
    string pattern = rnd.next("uniform|sameRow|sameCol|edgeCase");
    int N1, N2;
    if (pattern == "uniform") {
        N1 = rnd.next(1, maxN);
        do { N2 = rnd.next(1, maxN); } while (N2 == N1);
    }
    else if (pattern == "sameRow") {
        int cMax = (maxN - 1) / 4;
        if (cMax < 1) { // fallback
            N1 = rnd.next(1, maxN);
            do { N2 = rnd.next(1, maxN); } while (N2 == N1);
        } else {
            int r = rnd.next(0, 3);
            int c1 = rnd.next(0, cMax);
            int c2;
            do { c2 = rnd.next(0, cMax); } while (c2 == c1);
            N1 = c1 * 4 + r + 1;
            N2 = c2 * 4 + r + 1;
        }
    }
    else if (pattern == "sameCol") {
        int cMax = (maxN - 1) / 4;
        int c = rnd.next(0, cMax);
        int r1 = rnd.next(0, 3);
        int r2;
        do { r2 = rnd.next(0, 3); } while (r2 == r1);
        N1 = c * 4 + r1 + 1;
        N2 = c * 4 + r2 + 1;
    }
    else { // edgeCase
        N1 = rnd.next(1, min(10, maxN));
        N2 = rnd.next(max(1, maxN - 9), maxN);
        if (N1 == N2) {
            if (N2 < maxN) N2++;
            else N1--;
        }
    }
    // Final guard
    if (N1 < 1) N1 = 1;
    if (N2 < 1) N2 = 1;
    if (N1 > maxN) N1 = maxN;
    if (N2 > maxN) N2 = maxN;
    if (N1 == N2) {
        if (N1 < maxN) N2 = N1 + 1;
        else N1 = N2 - 1;
    }
    println(N1, N2);
    return 0;
}
