#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Choose N between 1 and 10
    int N = rnd.next(1, 10);
    // Choose M between N and min(N+20, 30)
    int maxDelta = min(20, 30 - N);
    int delta = 0;
    if (maxDelta > 0) {
        // Sometimes keep M = N to include minimal-sum cases
        if (rnd.next() < 0.3) {
            delta = 0;
        } else {
            delta = rnd.next(1, maxDelta);
        }
    }
    int M = N + delta;
    // Always pick the first sequence (K=1) to ensure validity
    int K = 1;
    println(N, M, K);
    return 0;
}
