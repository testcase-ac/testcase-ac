#include "testlib.h"

#include <vector>

using namespace std;

int clampM(long long value) {
    if (value < 1) return 1;
    if (value > 1000000) return 1000000;
    return static_cast<int>(value);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int m = 1;

    if (mode == 0) {
        m = rnd.next(1, 50);
    } else if (mode == 1) {
        m = rnd.next(999900, 1000000);
    } else if (mode == 2) {
        int base = rnd.any(vector<int>{2, 3, 4, 5, 6, 10});
        long long value = 1;
        while (value * base <= 1000000 && rnd.next(0, 2) != 0) {
            value *= base;
        }
        m = clampM(value + rnd.next(-2, 2));
    } else if (mode == 3) {
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        long long value = 1;
        int factors = rnd.next(2, 8);
        for (int i = 0; i < factors; ++i) {
            int p = rnd.any(primes);
            if (value * p > 1000000) break;
            value *= p;
        }
        m = static_cast<int>(value);
    } else if (mode == 4) {
        int q = rnd.next(1, 333333);
        m = clampM(3LL * q + rnd.next(-1, 1));
    } else if (mode == 5) {
        int q = rnd.next(1, 250000);
        m = clampM(4LL * q + rnd.next(-1, 1));
    } else if (mode == 6) {
        vector<int> anchors = {1, 2, 3, 4, 5, 6, 9, 16, 27, 64, 81, 243,
                               729, 2187, 6561, 19683, 59049, 177147, 531441,
                               999999, 1000000};
        m = clampM(rnd.any(anchors) + rnd.next(-3, 3));
    } else {
        m = rnd.next(1, 1000000);
    }

    println(m);
    return 0;
}
