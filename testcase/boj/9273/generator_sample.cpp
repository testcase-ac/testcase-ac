#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>
using namespace std;

static int boundedProduct(const vector<int>& factors) {
    int value = 1;
    for (int factor : factors) {
        if (value > 10000 / factor) {
            break;
        }
        value *= factor;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31,
                          37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
                          79, 83, 89, 97};
    vector<int> special = {1, 2, 3, 4, 6, 8, 12, 16, 24, 36, 60,
                           120, 360, 720, 840, 1260, 2520, 5040,
                           5000, 9999, 10000};

    int testCount = rnd.next(1, 40);
    set<int> values;

    while (int(values.size()) < testCount) {
        int mode = rnd.next(0, 7);
        int n = 1;

        if (mode == 0) {
            n = rnd.next(1, 30);
        } else if (mode == 1) {
            n = rnd.any(primes);
        } else if (mode == 2) {
            int base = rnd.any(vector<int>{2, 3, 5, 7, 10});
            int exp = rnd.next(1, 8);
            vector<int> factors(exp, base);
            n = boundedProduct(factors);
        } else if (mode == 3) {
            vector<int> factors;
            int factorCount = rnd.next(2, 6);
            for (int i = 0; i < factorCount; ++i) {
                factors.push_back(rnd.any(vector<int>{2, 2, 3, 3, 5, 7, 11}));
            }
            shuffle(factors.begin(), factors.end());
            n = boundedProduct(factors);
        } else if (mode == 4) {
            int x = rnd.next(1, 100);
            n = x * x;
        } else if (mode == 5) {
            n = rnd.next(9900, 10000);
        } else {
            n = rnd.any(special);
        }

        values.insert(n);
    }

    vector<int> output(values.begin(), values.end());
    shuffle(output.begin(), output.end());
    for (int n : output) {
        println("1/" + to_string(n));
    }

    return 0;
}
