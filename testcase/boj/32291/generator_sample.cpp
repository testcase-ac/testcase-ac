#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long boundedProduct(const vector<long long>& factors) {
    long long value = 1;
    for (long long factor : factors) {
        if (value > 1000000000001LL / factor) break;
        value *= factor;
    }
    return min(value, 1000000000001LL);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxX = 1000000000000LL;
    int mode = rnd.next(0, 7);
    long long x;

    if (mode == 0) {
        vector<long long> boundaries = {1, 2, 3, 998, maxX - 2, maxX - 1, maxX};
        x = rnd.any(boundaries);
    } else if (mode == 1) {
        x = rnd.next(1LL, 1000LL);
    } else if (mode == 2) {
        x = rnd.next(maxX - 10000, maxX);
    } else if (mode == 3) {
        long long base = rnd.next(2LL, 1000000LL);
        long long n = base * rnd.next(2LL, 1000000LL);
        x = min(n - 1, maxX);
    } else if (mode == 4) {
        vector<long long> factors;
        int count = rnd.next(2, 8);
        for (int i = 0; i < count; ++i) {
            factors.push_back(rnd.any(vector<long long>{2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31}));
        }
        x = max(1LL, boundedProduct(factors) - 1);
    } else if (mode == 5) {
        long long n = 1;
        long long base = rnd.any(vector<long long>{2, 3, 5, 10});
        while (n <= maxX / base && rnd.next(0, 1)) n *= base;
        while (n <= maxX / base) n *= base;
        x = n - 1;
    } else if (mode == 6) {
        long long root = rnd.next(2LL, 1000000LL);
        x = min(root * root - 1, maxX);
    } else {
        x = rnd.next(1LL, maxX);
    }

    println(x);
    return 0;
}
