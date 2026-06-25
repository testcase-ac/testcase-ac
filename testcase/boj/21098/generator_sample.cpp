#include "testlib.h"

#include <vector>

using namespace std;

long long randomPrimeLikeValue() {
    const vector<long long> primes = {
        2, 3, 5, 7, 11, 97, 999983, 999999937LL
    };
    return rnd.any(primes);
}

long long randomCompositeValue() {
    const vector<long long> composites = {
        4, 6, 8, 9, 12, 25, 100, 999999999LL, 1000000000LL
    };
    return rnd.any(composites);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    vector<long long> values;

    if (mode == 0) {
        values.push_back(1);
    } else if (mode == 1) {
        values.push_back(randomPrimeLikeValue());
    } else if (mode == 2) {
        values.push_back(randomCompositeValue());
    } else if (mode == 3) {
        values = {randomPrimeLikeValue(), randomPrimeLikeValue()};
    } else if (mode == 4) {
        long long a = rnd.next(1, 50);
        long long b = rnd.next(1, 50);
        if ((a + b) % 2 == 1) ++b;
        values = {a, b};
    } else if (mode == 5) {
        int n = rnd.next(3, 8);
        values.assign(n, 1);
        if (n == 3 && rnd.next(2) == 0) values[rnd.next(0, n - 1)] = rnd.next(2, 20);
    } else if (mode == 6) {
        int n = rnd.next(4, 20);
        for (int i = 0; i < n; ++i) values.push_back(rnd.next(1, 100));
    } else {
        int n = rnd.next(2, 12);
        const vector<long long> candidates = {
            1, 2, 3, 4, 5, 97, 999999999LL, 1000000000LL
        };
        for (int i = 0; i < n; ++i) values.push_back(rnd.any(candidates));
    }

    shuffle(values.begin(), values.end());
    println((int)values.size());
    println(values);

    return 0;
}
