#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47,
        53, 59, 61, 67, 71, 73, 79, 83, 89, 97
    };
    const vector<int> powers = {
        4, 8, 16, 32, 64, 81, 125, 243, 625, 1024, 3125,
        59049, 65536, 390625, 1048576, 4194304, 4782969
    };
    const vector<int> nearLimit = {
        4999991, 4999993, 4999995, 4999996, 4999998, 4999999, 5000000
    };

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 5 ? 80 : 35);
    vector<int> values;
    values.reserve(n);

    auto pushBoundedProduct = [&]() {
        long long x = 1;
        int factors = rnd.next(2, 7);
        for (int i = 0; i < factors; ++i) {
            int p = rnd.any(primes);
            if (x * p > 5000000) break;
            x *= p;
        }
        values.push_back((int)x);
    };

    while ((int)values.size() < n) {
        int pick = mode;
        if (mode == 5) pick = rnd.next(0, 4);

        if (pick == 0) {
            values.push_back(rnd.any(primes));
        } else if (pick == 1) {
            values.push_back(rnd.any(powers));
        } else if (pick == 2) {
            int p = rnd.any(primes);
            int q = rnd.any(primes);
            values.push_back(p * q);
        } else if (pick == 3) {
            pushBoundedProduct();
        } else {
            values.push_back(rnd.any(nearLimit));
        }
    }

    shuffle(values.begin(), values.end());

    println((int)values.size());
    println(values);

    return 0;
}
