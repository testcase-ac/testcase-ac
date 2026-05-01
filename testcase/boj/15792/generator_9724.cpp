#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int A = 1, B = 1;

    // Choose a scenario to diversify testcases
    int scenario = rnd.next(0, 6);

    if (scenario == 0) {
        // Small random numbers
        A = rnd.next(1, 10);
        B = rnd.next(1, 10);
    } else if (scenario == 1) {
        // 1 or small A over a prime B (repeating decimals)
        vector<int> primes = {3, 7, 11, 13, 17, 19, 23, 29,
                              37, 41, 43, 47, 53, 59, 61, 67,
                              71, 73, 79, 83, 89, 97};
        B = rnd.any(primes);
        if (rnd.next(0, 1) == 0) {
            A = 1;
        } else {
            A = rnd.next(1, B - 1);
        }
    } else if (scenario == 2) {
        // Terminating decimal: denominator with only 2s and 5s
        while (true) {
            int e2 = rnd.next(0, 10);
            int e5 = rnd.next(0, 6);
            long long denom = 1;
            for (int i = 0; i < e2; ++i) denom *= 2;
            for (int i = 0; i < e5; ++i) denom *= 5;
            if (denom >= 2 && denom <= 10000) {
                B = (int)denom;
                break;
            }
        }
        A = rnd.next(1, 10000);
    } else if (scenario == 3) {
        // A > B with common factor (non-reduced fraction)
        int g = rnd.next(2, 10);
        int limit = 10000 / g;
        int k1 = rnd.next(1, limit);
        int k2 = rnd.next(1, limit);
        A = k1 * g;
        B = k2 * g;
        if (A <= B) swap(A, B);
        if (A > 10000 || B < 1) {
            A = 9990;
            B = 3330;
        }
    } else if (scenario == 4) {
        // Near upper bounds
        A = rnd.next(9000, 10000);
        B = rnd.next(9000, 10000);
    } else if (scenario == 5) {
        // Very small ratio
        A = rnd.next(1, 50);
        B = rnd.next(5000, 10000);
    } else if (scenario == 6) {
        // Handpicked interesting fractions
        vector<pair<int,int>> samples = {
            {1, 2},
            {1, 3},
            {2, 3},
            {1, 6},
            {3, 7},
            {22, 7},
            {355, 113},
            {9999, 10000},
            {10000, 9999}
        };
        auto p = rnd.any(samples);
        A = p.first;
        B = p.second;
    }

    println(A, B);
    return 0;
}
