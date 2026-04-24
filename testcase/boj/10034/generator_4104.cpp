#include "testlib.h"
#include <vector>
#include <cstdint>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Precompute powers of 10
    vector<long long> p10(19);
    p10[0] = 1;
    for (int i = 1; i <= 18; ++i) {
        p10[i] = p10[i-1] * 10;
    }

    // Hyper-parameters for diversity
    int lenX = rnd.next(3, 6);  // number of digits for X
    vector<long long> widthOptions = {10, 100, 500, 1000};
    long long maxWidth = rnd.any(widthOptions);

    // Determine bounds for X and Y
    long long lo = p10[lenX-1];
    long long hiBase = p10[lenX] - 1;
    long long maxRange = min(maxWidth, hiBase - lo);

    // Ensure at least a difference of 1
    long long d = rnd.next(1LL, maxRange);
    long long X = rnd.next(lo, hiBase - d);
    long long Y = X + d;

    // Output one test case
    println(X, Y);

    return 0;
}
