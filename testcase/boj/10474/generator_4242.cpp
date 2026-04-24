#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small and diverse
    int T = rnd.next(1, 7);

    for (int tc = 0; tc < T; ++tc) {
        // Hyper-parameter: occasionally pick denom = 1
        int denom;
        if (rnd.next() < 0.15) {
            denom = 1;
        } else {
            denom = rnd.next(2, 50);
        }

        // Choose type: 0 = pure fraction, 1 = exact divisible, 2 = mixed
        int type;
        if (denom == 1) {
            type = 1; // only divisible makes sense
        } else {
            type = rnd.next(0, 2);
        }

        long long N, R, I;
        if (type == 0) {
            // pure fraction: 0 < N < denom
            R = rnd.next(1, denom - 1);
            I = 0;
            N = R;
        } else if (type == 1) {
            // exact divisible: N = I * denom
            I = rnd.next(1, 10);
            R = 0;
            N = I * denom;
        } else {
            // mixed: N = I * denom + R, 1 <= R < denom
            I = rnd.next(1, 10);
            R = rnd.next(1, denom - 1);
            N = I * denom + R;
        }

        // Output numerator and denominator
        println(N, denom);
    }

    // Termination line
    println(0, 0);

    return 0;
}
