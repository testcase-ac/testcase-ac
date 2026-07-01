#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

long long randomKNearPowerOfTwo(int n) {
    int exponent = rnd.next(0, min(n - 1, 60));
    long long value = 1LL << exponent;
    long long delta = rnd.next(0LL, min(20LL, value - 1));
    if (rnd.next(2) == 0) {
        return max(1LL, value - delta);
    }
    return min(1000000000000000000LL, value + delta);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    long long k;

    if (mode == 0) {
        n = rnd.next(1, 8);
        k = rnd.next(1LL, 100LL);
    } else if (mode == 1) {
        n = rnd.next(9, 25);
        k = rnd.next(1LL, 1000000LL);
    } else if (mode == 2) {
        n = rnd.next(80, 100);
        k = rnd.next(1LL, 1000000000000000000LL);
    } else if (mode == 3) {
        vector<long long> edgeK = {
            1LL,
            2LL,
            3LL,
            999999999999999999LL,
            1000000000000000000LL,
        };
        n = rnd.any(vector<int>{1, 2, 3, 4, 5, 99, 100});
        k = rnd.any(edgeK);
    } else if (mode == 4) {
        n = rnd.next(2, 65);
        k = randomKNearPowerOfTwo(n);
    } else {
        n = rnd.next(1, 100);
        long long upper = rnd.any(vector<long long>{
            10LL,
            1000LL,
            1000000000LL,
            1000000000000000000LL,
        });
        k = rnd.next(1LL, upper);
    }

    println(n, k);
    return 0;
}
