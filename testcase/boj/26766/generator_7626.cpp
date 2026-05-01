#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // We generate N in various regimes to catch edge and performance cases.
    // 1) N = 1 (edge)
    // 2) small: 2..10
    // 3) medium: 11..100
    // 4) large1: 101..1000
    // 5) large2: 1001..10000 or 10001..100000
    double p = rnd.next();
    int N;
    if (p < 0.1) {
        // edge case: minimal
        N = 1;
    } else if (p < 0.3) {
        // small cases
        N = rnd.next(2, 10);
    } else if (p < 0.6) {
        // medium cases
        N = rnd.next(11, 100);
    } else if (p < 0.85) {
        // larger but still manageable
        N = rnd.next(101, 1000);
    } else {
        // very large cases, split into two subranges
        if (rnd.next(0, 1) == 0) {
            N = rnd.next(1001, 10000);
        } else {
            N = rnd.next(10001, 100000);
        }
    }

    println(N);
    return 0;
}
