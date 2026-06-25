#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

vector<int> primesUpTo1000() {
    vector<int> primes;
    for (int x = 2; x <= 1000; ++x) {
        bool prime = true;
        for (int d = 2; d * d <= x; ++d) {
            if (x % d == 0) {
                prime = false;
                break;
            }
        }
        if (prime) {
            primes.push_back(x);
        }
    }
    return primes;
}

vector<pair<int, int>> makeCase(const vector<int>& primes, int mode) {
    int c;
    vector<int> chosen = primes;

    if (mode == 0) {
        c = 1;
    } else if (mode == 1) {
        c = rnd.next(1, 3);
    } else if (mode == 2) {
        c = rnd.next(4, 8);
    } else if (mode == 3) {
        c = rnd.next(10, 15);
    } else {
        c = rnd.next(1, 15);
    }

    shuffle(chosen.begin(), chosen.end());
    chosen.resize(c);

    vector<pair<int, int>> factors;
    for (int i = 0; i < c; ++i) {
        int exponent;
        if (mode == 0) {
            exponent = rnd.any(vector<int>{1, 2, 50});
        } else if (mode == 1) {
            exponent = rnd.next(1, 5);
        } else if (mode == 2) {
            exponent = rnd.next(1, 20);
        } else if (mode == 3) {
            exponent = rnd.next(35, 50);
        } else {
            exponent = rnd.any(vector<int>{1, rnd.next(2, 49), 50});
        }
        factors.push_back({chosen[i], exponent});
    }

    if (rnd.next(2) == 0) {
        sort(factors.begin(), factors.end());
    } else {
        shuffle(factors.begin(), factors.end());
    }
    return factors;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = primesUpTo1000();
    int t = rnd.next(6, 18);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc < 5 ? tc : rnd.next(0, 4);
        vector<pair<int, int>> factors = makeCase(primes, mode);

        println((int)factors.size());
        for (const auto& factor : factors) {
            println(factor.first, factor.second);
        }
    }

    return 0;
}
