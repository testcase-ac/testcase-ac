#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long boundedProduct(const vector<int>& factors) {
    long long value = 1;
    for (int factor : factors) {
        if (value > 2147483647LL / factor) break;
        value *= factor;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 30);
    vector<int> numbers;
    numbers.reserve(t);

    vector<int> oddPrimes = {3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

    for (int caseId = 0; caseId < t; ++caseId) {
        int mode = rnd.next(0, 6);
        long long n = 1;

        if (mode == 0) {
            n = 1LL << rnd.next(1, 30);
        } else if (mode == 1) {
            n = rnd.next(1, 1000000000) * 2LL - 1;
        } else if (mode == 2) {
            int len = rnd.next(2, 7);
            vector<int> factors;
            for (int i = 0; i < len; ++i) factors.push_back(rnd.any(oddPrimes));
            n = boundedProduct(factors) * (1LL << rnd.next(0, 8));
        } else if (mode == 3) {
            int len = rnd.next(2, 8);
            long long first = rnd.next(1, 1000);
            n = len * (2 * first + len - 1) / 2;
        } else if (mode == 4) {
            n = 2147483647LL - rnd.next(0, 2000);
        } else if (mode == 5) {
            n = rnd.next(1, 200);
        } else {
            n = rnd.next(1, 2147483647);
        }

        numbers.push_back(static_cast<int>(max(1LL, min(2147483647LL, n))));
    }

    shuffle(numbers.begin(), numbers.end());

    println(t);
    for (int n : numbers) println(n);

    return 0;
}
