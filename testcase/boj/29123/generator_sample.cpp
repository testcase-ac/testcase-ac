#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long randomProduct(const vector<int>& factors, int minCount, int maxCount) {
    int count = rnd.next(minCount, maxCount);
    long long value = 1;
    for (int i = 0; i < count; ++i) {
        vector<int> candidates;
        for (int factor : factors) {
            if (value <= 1000000000LL / factor) {
                candidates.push_back(factor);
            }
        }
        if (candidates.empty()) {
            break;
        }
        value *= rnd.any(candidates);
    }
    return value;
}

long long randomProductAtMost(const vector<int>& factors, int minCount, int maxCount, long long limit) {
    int count = rnd.next(minCount, maxCount);
    long long value = 1;
    for (int i = 0; i < count; ++i) {
        vector<int> candidates;
        for (int factor : factors) {
            if (value <= limit / factor) {
                candidates.push_back(factor);
            }
        }
        if (candidates.empty()) {
            break;
        }
        value *= rnd.any(candidates);
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> smallPrimes = {2, 3, 5, 7, 11, 13, 17, 19};
    long long a = 1;
    long long b = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        vector<long long> values = {1, 2, 3, 4, 6, 8, 12, 24, 36};
        a = rnd.any(values);
        b = rnd.any(values);
    } else if (mode == 1) {
        a = randomProduct(smallPrimes, 1, 10);
        b = a;
    } else if (mode == 2) {
        a = randomProduct({2}, 0, 29);
        b = randomProduct({3}, 0, 18);
    } else if (mode == 3) {
        long long common = randomProduct({2, 3, 5}, 1, 8);
        long long left = randomProductAtMost({7, 11, 13}, 0, 5, 1000000000LL / common);
        long long right = randomProductAtMost({17, 19, 23}, 0, 4, 1000000000LL / common);
        a = common * left;
        b = common * right;
    } else if (mode == 4) {
        vector<long long> nearLimit = {
            999999937LL, 999999938LL, 999999939LL, 999999940LL,
            1000000000LL, 1000000000LL - rnd.next(0, 1000)
        };
        a = rnd.any(nearLimit);
        b = rnd.any(nearLimit);
    } else {
        a = rnd.next(1, 1000000000);
        b = rnd.next(1, 1000000000);
    }

    if (rnd.next(0, 1)) {
        swap(a, b);
    }

    println(a, b);
    return 0;
}
