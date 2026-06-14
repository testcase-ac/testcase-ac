#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_X = 100000;

vector<int> buildPrimes(int limit) {
    vector<int> primes;
    vector<bool> composite(limit + 1);
    for (int i = 2; i <= limit; ++i) {
        if (!composite[i]) {
            primes.push_back(i);
            if (1LL * i * i <= limit) {
                for (long long j = 1LL * i * i; j <= limit; j += i) {
                    composite[j] = true;
                }
            }
        }
    }
    return primes;
}

int clampValue(int x) {
    return max(1, min(MAX_X, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = buildPrimes(MAX_X);
    int T = rnd.next(3, 10);
    vector<vector<int>> tests;

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        int n;
        if (tc == T - 1 && rnd.next(0, 3) == 0) {
            n = 200;
        } else if (mode <= 2) {
            n = rnd.next(1, 20);
        } else {
            n = rnd.next(20, 80);
        }

        vector<int> x;
        if (mode == 0) {
            int center = rnd.next(1, MAX_X);
            int radius = rnd.next(0, 5);
            for (int i = 0; i < n; ++i) {
                x.push_back(clampValue(center + rnd.next(-radius, radius)));
            }
        } else if (mode == 1) {
            int start = rnd.next(0, (int)primes.size() - n);
            for (int i = 0; i < n; ++i) {
                int delta = rnd.next(-3, 3);
                x.push_back(clampValue(primes[start + i] + delta));
            }
            shuffle(x.begin(), x.end());
        } else if (mode == 2) {
            for (int i = 0; i < n; ++i) {
                if (rnd.next(0, 1) == 0) {
                    x.push_back(rnd.next(1, 25));
                } else {
                    x.push_back(rnd.next(99975, MAX_X));
                }
            }
        } else if (mode == 3) {
            int lo = rnd.next(1, 95000);
            int hi = rnd.next(lo, min(MAX_X, lo + rnd.next(20, 5000)));
            for (int i = 0; i < n; ++i) {
                x.push_back(rnd.next(lo, hi));
            }
        } else if (mode == 4) {
            int pivot = rnd.any(primes);
            for (int i = 0; i < n; ++i) {
                int sign = rnd.next(0, 1) == 0 ? -1 : 1;
                int distance = rnd.wnext(5000, -2);
                x.push_back(clampValue(pivot + sign * distance));
            }
        } else {
            for (int i = 0; i < n; ++i) {
                int bucket = rnd.next(0, 3);
                if (bucket == 0) x.push_back(rnd.next(1, 100));
                if (bucket == 1) x.push_back(rnd.next(101, 10000));
                if (bucket == 2) x.push_back(rnd.next(10001, 90000));
                if (bucket == 3) x.push_back(rnd.next(90001, MAX_X));
            }
        }

        tests.push_back(x);
    }

    println((int)tests.size());
    for (const vector<int>& x : tests) {
        println((int)x.size());
        println(x);
    }

    return 0;
}
