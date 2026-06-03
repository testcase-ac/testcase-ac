#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

namespace {

const long long INT32_MAX_VALUE = 2147483647LL;
const int MAX_VALUE = 1000000;

const vector<int> SMALL_PRIMES = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
const vector<int> LARGE_FACTORS = {999983, 999979, 1000000, 999950, 720720};

void addRandomReducedFactors(vector<int>& factors, long long& product, int attempts,
                             int mode) {
    for (int i = 0; i < attempts; ++i) {
        int p;
        if (mode == 0) {
            p = rnd.any(SMALL_PRIMES);
        } else if (mode == 1) {
            p = rnd.next(2, 97);
        } else {
            p = rnd.any(vector<int>{2, 3, 5, 7, 11, 999983});
        }

        if (product <= INT32_MAX_VALUE / p) {
            factors.push_back(p);
            product *= p;
        }
    }
}

void addCommonFactors(vector<int>& aFactors, vector<int>& bFactors, int count,
                      bool useLargeFactors) {
    for (int i = 0; i < count; ++i) {
        int x = useLargeFactors && rnd.next(0, 3) == 0 ? rnd.any(LARGE_FACTORS)
                                                       : rnd.any(SMALL_PRIMES);
        aFactors.push_back(x);
        bFactors.push_back(x);
    }
}

vector<int> packFactors(vector<int> factors) {
    shuffle(factors.begin(), factors.end());

    vector<int> values;
    for (int f : factors) {
        bool placed = false;
        shuffle(values.begin(), values.end());
        for (int& value : values) {
            if (value <= MAX_VALUE / f) {
                value *= f;
                placed = true;
                break;
            }
        }
        if (!placed) {
            values.push_back(f);
        }
    }

    int ones = rnd.next(0, 3);
    while (ones--) {
        values.push_back(1);
    }
    if (values.empty()) {
        values.push_back(1);
    }
    shuffle(values.begin(), values.end());
    return values;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 4);
        vector<int> numeratorFactors;
        vector<int> denominatorFactors;
        long long numerator = 1;
        long long denominator = 1;

        if (mode != 0 && mode != 2) {
            addRandomReducedFactors(numeratorFactors, numerator, rnd.next(1, 9),
                                    rnd.next(0, 2));
        }
        if (mode != 0 && mode != 1) {
            addRandomReducedFactors(denominatorFactors, denominator,
                                    rnd.next(1, 9), rnd.next(0, 2));
        }

        addCommonFactors(numeratorFactors, denominatorFactors, rnd.next(0, 12),
                         mode == 4);

        vector<int> a = packFactors(numeratorFactors);
        vector<int> b = packFactors(denominatorFactors);

        println(static_cast<int>(a.size()), static_cast<int>(b.size()));
        println(a);
        println(b);
    }

    return 0;
}
