#include "testlib.h"
#include <vector>
#include <cmath>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Helper to generate a double with two decimal digits in (0, 1e8]
    auto genVal = [&]() {
        // Occasionally pick exact boundary to catch edge cases
        if (rnd.next(0, 9) == 0) {
            if (rnd.next(0, 1) == 0) return 0.01;
            else return 1e8;
        }
        // Diverse ranges: tiny, small, medium, large
        vector<pair<double, double>> ranges = {
            {0.01, 1.00},
            {1.00, 100.00},
            {100.00, 10000.00},
            {10000.00, 1e8}
        };
        auto pr = rnd.any(ranges);
        double lo = pr.first, hi = pr.second;
        double x = rnd.next(lo, hi);
        // Round to two decimals
        x = floor(x * 100.0 + 0.5) / 100.0;
        // Clamp to ensure within bounds
        if (x < lo) x = lo;
        if (x > hi) x = hi;
        return x;
    };

    double A = genVal();
    double B = genVal();
    // Output with two decimal places
    printf("%.2f %.2f\n", A, B);

    return 0;
}
