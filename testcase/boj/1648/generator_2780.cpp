#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    double p = rnd.next();
    int N, M;
    if (p < 0.2) {
        // Force odd dimensions so area is odd (tiling impossible)
        vector<int> odds = {1, 3, 5, 7, 9, 11, 13};
        N = rnd.any(odds);
        M = rnd.any(odds);
    } else if (p < 0.4) {
        // Small N, arbitrary M
        N = rnd.next(1, 3);
        M = rnd.next(1, 14);
    } else if (p < 0.6) {
        // Small M, arbitrary N
        M = rnd.next(1, 3);
        N = rnd.next(1, 14);
    } else {
        // Full-range with weighted bias towards extremes or middle
        int tN = rnd.next(-3, 3);
        int tM = rnd.next(-3, 3);
        N = rnd.wnext(14, tN) + 1; // produces 1..14
        M = rnd.wnext(14, tM) + 1;
    }

    // Ensure within limits
    N = min(max(N, 1), 14);
    M = min(max(M, 1), 14);

    println(N, M);
    return 0;
}
