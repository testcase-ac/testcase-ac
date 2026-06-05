#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<int> smallPrimes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47
    };
    const vector<int> smallComposites = {
        0, 1, 4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 22, 24
    };
    vector<int> boundaryValues = {
        0, 1, 2, 3, 4, 4999991, 4999993, 4999995, 4999998, 4999999
    };

    int mode = rnd.next(0, 4);
    int n = rnd.next(5, mode == 4 ? 40 : 18);
    vector<pair<int, int>> rounds;
    rounds.reserve(n);

    auto randomPrime = [&]() {
        return rnd.any(smallPrimes);
    };
    auto randomComposite = [&]() {
        return rnd.any(smallComposites);
    };
    auto randomMixed = [&]() {
        int kind = rnd.next(0, 4);
        if (kind <= 1) return randomPrime();
        if (kind <= 3) return randomComposite();
        return rnd.any(boundaryValues);
    };

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            rounds.push_back({randomMixed(), randomMixed()});
        }
    } else if (mode == 1) {
        int daewoongRepeat = randomPrime();
        int gyuseongRepeat = randomPrime();
        for (int i = 0; i < n; ++i) {
            int a = (i % 3 == 0) ? daewoongRepeat : randomMixed();
            int b = (i % 4 == 0) ? gyuseongRepeat : randomMixed();
            rounds.push_back({a, b});
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int a = (rnd.next(0, 3) == 0) ? randomPrime() : randomComposite();
            int b = (rnd.next(0, 3) == 0) ? randomPrime() : randomComposite();
            rounds.push_back({a, b});
        }
    } else if (mode == 3) {
        shuffle(boundaryValues.begin(), boundaryValues.end());
        for (int i = 0; i < n; ++i) {
            int a = (i < (int)boundaryValues.size()) ? boundaryValues[i] : randomMixed();
            int b = (i + 3 < (int)boundaryValues.size()) ? boundaryValues[i + 3] : randomMixed();
            rounds.push_back({a, b});
        }
    } else {
        vector<int> primes = smallPrimes;
        shuffle(primes.begin(), primes.end());
        for (int i = 0; i < n; ++i) {
            int a = i < (int)primes.size() ? primes[i] : randomMixed();
            int b = (i % 2 == 0) ? randomComposite() : randomPrime();
            if (rnd.next(0, 5) == 0) b = a;
            rounds.push_back({a, b});
        }
    }

    println(n);
    for (auto [a, b] : rounds) {
        println(a, b);
    }

    return 0;
}
