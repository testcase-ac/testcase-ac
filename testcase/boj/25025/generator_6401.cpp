#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose a small prime P for manual verification
    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int P = rnd.any(primes);

    // Hyper-parameter: sometimes small N, sometimes larger
    int N = (rnd.next(0,1) ? rnd.next(6, 20) : rnd.next(0, 5));

    // Occasionally pick a simple polynomial (all ones)
    bool simple = (rnd.next(0, 9) == 0);

    // Generate coefficients a_N ... a_0
    vector<long long> coeff(N + 1);
    for (int i = 0; i <= N; i++) {
        if (simple) {
            coeff[i] = 1;
        } else {
            // mix small (< P) and large coefficients
            if (rnd.next(0, 1) == 0) {
                coeff[i] = rnd.next(0, P - 1);
            } else {
                coeff[i] = rnd.next(P, 1000000000);
            }
        }
    }

    // Output
    println(N, P);
    println(coeff);

    return 0;
}
