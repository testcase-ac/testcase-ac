#include "testlib.h"
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAXV = 10000000000000000LL; // 10^16

    // Choose a scenario to get diverse edge and random cases
    int scenario = rnd.next(0, 4);
    long long A, B;

    switch (scenario) {
        // small range [1..100]
        case 0:
            A = rnd.next(1LL, 100LL);
            B = rnd.next(A, min(100LL, MAXV));
            break;

        // single-element range
        case 1:
            A = rnd.next(1LL, MAXV);
            B = A;
            break;

        // small delta from a random start in [1..MAX/2]
        case 2: {
            A = rnd.next(1LL, MAXV / 2);
            long long delta = rnd.next(0LL, 100000LL);
            B = min(MAXV, A + delta);
            break;
        }

        // fully random large range
        case 3:
            A = rnd.next(1LL, MAXV - 1);
            B = rnd.next(A + 1, MAXV);
            break;

        // full boundary case
        default:
            A = 1;
            B = MAXV;
            break;
    }

    println(A, B);
    return 0;
}
