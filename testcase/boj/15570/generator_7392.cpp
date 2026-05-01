#include "testlib.h"
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter types to cover edge and varied cases
    int type = rnd.next(0, 3);
    int N;
    long long M;
    const long long MMAX = 10000000000LL;
    switch (type) {
        // Minimal N, small M
        case 0:
            N = 1;
            M = rnd.next(1LL, 10LL);
            break;
        // Medium N, medium M
        case 1:
            N = rnd.next(2, 50);
            M = rnd.next(1LL, 1000000LL);
            break;
        // Large N, large M
        case 2:
            N = rnd.next(50, 100);
            M = rnd.next(1000000000LL, MMAX);
            break;
        // Fully random within constraints
        default:
            N = rnd.next(1, 100);
            M = rnd.next(1LL, MMAX);
            break;
    }
    println(N, M);
    return 0;
}
