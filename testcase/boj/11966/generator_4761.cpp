#include "testlib.h"
#include <cstdint>
#include <vector>
using namespace std;

bool isPowerOfTwo(int64_t x) {
    return x > 0 && (x & (x - 1)) == 0;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAXV = 1 << 30; // maximum N

    // Decide whether to generate a power of two or not
    bool wantPow = rnd.next(0, 1) == 1;

    int64_t N;
    if (wantPow) {
        // Choose exponent distribution: uniform (0), bias small (-3), bias large (+3)
        vector<int> expBias = {0, -3, 3};
        int b = rnd.any(expBias);
        int e;
        if (b == 0) {
            e = rnd.next(0, 30);
        } else {
            // weighted exponent in [0..30]
            e = rnd.wnext(31, b);
        }
        N = (int64_t)1 << e;
    } else {
        // Generate a non-power-of-two with various biases
        int distType = rnd.next(0, 2);
        while (true) {
            if (distType == 0) {
                // uniform in [1..MAXV]
                N = rnd.next(1, MAXV);
            } else if (distType == 1) {
                // bias toward small values
                N = rnd.wnext(MAXV, -3) + 1;
            } else {
                // bias toward large values
                N = rnd.wnext(MAXV, 3) + 1;
            }
            if (!isPowerOfTwo(N)) break;
        }
    }

    // Output the single test case
    println(N);
    return 0;
}
