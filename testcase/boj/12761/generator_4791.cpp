#include "testlib.h"
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose A and B either coprime or not
    int A, B;
    if (rnd.next(0,1) == 0) {
        // ensure gcd(A,B) = 1
        do {
            A = rnd.next(2, 10);
            B = rnd.next(2, 10);
        } while (std::gcd(A, B) != 1);
    } else {
        // ensure gcd(A,B) > 1
        do {
            A = rnd.next(2, 10);
            B = rnd.next(2, 10);
        } while (std::gcd(A, B) == 1);
    }

    // Hyper-parameter: small or larger position range for hand-checkability
    bool smallRange = rnd.next(0,1) == 0;
    int maxRange = smallRange ? rnd.next(20, 50) : rnd.next(51, 100);

    // Decide if positions are the same (edge case) with ~10% chance
    bool equalPos = (rnd.next(0,9) == 0);

    int N = rnd.next(0, maxRange);
    int M;
    if (equalPos) {
        M = N;
    } else {
        // ensure M != N
        do {
            M = rnd.next(0, maxRange);
        } while (M == N);
    }

    // Output the single test-case
    println(A, B, N, M);
    return 0;
}
