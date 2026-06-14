#include "testlib.h"

#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> factorialDigits;
    double logSum = 0.0;
    for (int x = 1; ; ++x) {
        logSum += log10((double)x);
        int digits = (int)floor(logSum + 1e-12) + 1;
        if (digits > 150000) break;
        factorialDigits.push_back(digits);
    }

    int n;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        n = rnd.next(1, 30);
    } else if (mode == 1) {
        n = rnd.next(149000, 150000);
    } else if (mode == 2) {
        n = rnd.next(1, 150000);
    } else if (mode == 3) {
        int d = rnd.any(factorialDigits);
        n = max(1, min(150000, d + rnd.next(-2, 2)));
    } else {
        int base = 1;
        int exponent = rnd.next(0, 5);
        for (int i = 0; i < exponent; ++i) base *= 10;
        n = max(1, min(150000, base + rnd.next(-20, 200)));
    }

    println(n);
    return 0;
}
