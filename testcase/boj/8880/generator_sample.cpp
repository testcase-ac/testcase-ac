#include "testlib.h"

#include <algorithm>
#include <climits>
#include <set>
#include <vector>

using namespace std;

const long long LIMIT = LLONG_MAX;
const int PRIMES[20] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                        31, 37, 41, 43, 47, 53, 59, 61, 67, 71};

long long multinomial(const vector<int>& exponents) {
    __int128 result = 1;
    int used = 0;
    for (int exponent : exponents) {
        for (int i = 1; i <= exponent; i++) {
            result *= used + i;
            result /= i;
            if (result > LIMIT) {
                return LIMIT;
            }
        }
        used += exponent;
    }
    return static_cast<long long>(result);
}

bool productFits(const vector<int>& exponents) {
    __int128 product = 1;
    for (int i = 0; i < static_cast<int>(exponents.size()); i++) {
        for (int j = 0; j < exponents[i]; j++) {
            product *= PRIMES[i];
            if (product > LIMIT) {
                return false;
            }
        }
    }
    return true;
}

vector<int> randomProfile() {
    int mode = rnd.next(0, 4);
    vector<int> exponents;

    if (mode == 0) {
        exponents.push_back(rnd.next(1, 28));
    } else if (mode == 1) {
        int terms = rnd.next(2, 10);
        exponents.assign(terms, 1);
    } else if (mode == 2) {
        int terms = rnd.next(2, 8);
        int last = rnd.next(2, 14);
        for (int i = 0; i < terms; i++) {
            int exponent = rnd.next(1, last);
            exponents.push_back(exponent);
            last = exponent;
        }
    } else if (mode == 3) {
        int terms = rnd.next(3, 12);
        for (int i = 0; i < terms; i++) {
            exponents.push_back(rnd.wnext(8, -2) + 1);
        }
        sort(exponents.rbegin(), exponents.rend());
    } else {
        int terms = rnd.next(12, 20);
        exponents.assign(terms, 1);
        int extra = rnd.next(0, 12);
        for (int i = 0; i < extra; i++) {
            int idx = rnd.next(terms);
            exponents[idx]++;
        }
        sort(exponents.rbegin(), exponents.rend());
    }

    while (!exponents.empty() && !productFits(exponents)) {
        int idx = rnd.next(static_cast<int>(exponents.size()));
        exponents[idx]--;
        if (exponents[idx] == 0) {
            exponents.erase(exponents.begin() + idx);
        }
        sort(exponents.rbegin(), exponents.rend());
    }

    if (exponents.empty()) {
        exponents.push_back(1);
    }
    return exponents;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(12, 45);
    set<long long> values;
    values.insert(1);

    while (static_cast<int>(values.size()) < testCases) {
        vector<int> profile = randomProfile();
        long long n = multinomial(profile);
        if (n >= 1 && n < LIMIT) {
            values.insert(n);
        }
    }

    vector<long long> output(values.begin(), values.end());
    shuffle(output.begin(), output.end());
    for (long long n : output) {
        println(n);
    }

    return 0;
}
