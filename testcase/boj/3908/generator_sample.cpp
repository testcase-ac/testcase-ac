#include "testlib.h"

#include <numeric>
#include <utility>
#include <vector>

using namespace std;

vector<int> primesUpTo(int limit) {
    vector<int> primes;
    for (int x = 2; x <= limit; ++x) {
        bool prime = true;
        for (int d = 2; d * d <= x; ++d) {
            if (x % d == 0) {
                prime = false;
                break;
            }
        }
        if (prime) primes.push_back(x);
    }
    return primes;
}

pair<int, int> randomPrimeSumCase(const vector<int>& primes) {
    int k = rnd.next(1, 7);
    vector<int> pool;
    for (int p : primes) {
        if (p <= 220) pool.push_back(p);
    }
    shuffle(pool.begin(), pool.end());

    int sum = accumulate(pool.begin(), pool.begin() + k, 0);
    while (sum > 1120) {
        shuffle(pool.begin(), pool.end());
        sum = accumulate(pool.begin(), pool.begin() + k, 0);
    }

    return {sum, k};
}

pair<int, int> edgeCase() {
    vector<pair<int, int>> cases = {
        {1, 1},    {2, 1},    {3, 1},    {4, 2},    {5, 2},
        {17, 4},   {24, 2},   {24, 3},   {100, 5},  {1119, 1},
        {1120, 1}, {1120, 13}, {1120, 14}, {1, 14},  {50, 14},
    };
    return rnd.any(cases);
}

pair<int, int> biasedRandomCase() {
    int kMode = rnd.next(0, 4);
    int k = 1;
    if (kMode == 0) {
        k = rnd.next(1, 3);
    } else if (kMode == 1) {
        k = rnd.next(4, 8);
    } else if (kMode == 2) {
        k = rnd.next(9, 14);
    } else {
        k = rnd.any(vector<int>{1, 2, 13, 14});
    }

    int nMode = rnd.next(0, 4);
    int n = 1;
    if (nMode == 0) {
        n = rnd.next(1, 40);
    } else if (nMode == 1) {
        n = rnd.next(41, 180);
    } else if (nMode == 2) {
        n = rnd.next(181, 700);
    } else {
        n = rnd.next(900, 1120);
    }

    return {n, k};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = primesUpTo(1120);
    int t = rnd.next(12, 35);
    vector<pair<int, int>> tests;

    tests.push_back(edgeCase());
    tests.push_back(edgeCase());
    tests.push_back({1120, 14});

    while ((int)tests.size() < t) {
        int mode = rnd.next(0, 99);
        if (mode < 30) {
            tests.push_back(edgeCase());
        } else if (mode < 60) {
            tests.push_back(randomPrimeSumCase(primes));
        } else {
            tests.push_back(biasedRandomCase());
        }
    }

    shuffle(tests.begin(), tests.end());

    println((int)tests.size());
    for (auto [n, k] : tests) {
        println(n, k);
    }

    return 0;
}
