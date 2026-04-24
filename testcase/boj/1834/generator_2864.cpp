#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int N;
    // With some probability, pick a small N for corner cases
    if (rnd.next() < 0.3) {
        N = rnd.next(1, 10);
    } else {
        // Use weighted selection to skew towards large or small values
        int t = rnd.next(-3, 3);
        // rnd.wnext(2000000, t) gives [0, 1999999], so add 1
        N = rnd.wnext(2000000, t) + 1;
    }

    // Ensure within bounds [1, 2e6]
    N = max(1, min(2000000, N));
    println(N);
    return 0;
}
