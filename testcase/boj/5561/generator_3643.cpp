#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose small even N between 2 and 10
    int N2 = rnd.next(1, 5);
    int N = N2 * 2;
    // Hyper-parameter: max possible cut cost (ensure >=1 to avoid invalid ranges)
    int maxP = rnd.next(1, 20);
    // Distribution type for diversity: 0=uniform, 1=zero-heavy, 2=high-heavy
    int distType = rnd.next(0, 2);

    vector<int> P(N+1);
    // Fill P[1..N-1] according to distType
    for (int i = 1; i < N; i++) {
        if (distType == 0) {
            // uniform 0..maxP
            P[i] = rnd.next(0, maxP);
        } else if (distType == 1) {
            // zero-heavy: many zeros
            if (rnd.next() < 0.5) P[i] = 0;
            else P[i] = rnd.next(1, maxP);
        } else {
            // high-heavy: more large values
            int lo = maxP / 2;
            P[i] = rnd.next(lo, maxP);
        }
    }

    // With some probability, force a two-cut solution better than single cut at N/2
    if (N > 2 && maxP >= 3 && rnd.next() < 0.3) {
        int half = N / 2;
        int i = rnd.next(1, half - 1);
        int j = half + i;  // ensures segments of length i and N-j sum to half
        if (j < N) {
            int smallMax = maxP / 5;
            if (smallMax < 1) smallMax = 1;
            P[i] = rnd.next(0, smallMax);
            P[j] = rnd.next(0, smallMax);
            int needed = P[i] + P[j] + 1;
            if (needed > maxP) needed = maxP;
            P[half] = rnd.next(needed, maxP);
        }
    }

    // Output
    println(N);
    for (int i = 1; i < N; i++) {
        println(P[i]);
    }
    return 0;
}
