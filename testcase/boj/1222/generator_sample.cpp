#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampValue(long long x) {
    return (int)min<long long>(2000000, max<long long>(1, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 24);
    vector<int> a;

    if (mode == 0) {
        int value = rnd.next(1, 60);
        n = rnd.next(2, 18);
        a.assign(n, value);
    } else if (mode == 1) {
        int base = rnd.next(2, 80);
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) {
            int multiplier = rnd.next(1, 30);
            a.push_back(clampValue(1LL * base * multiplier));
        }
    } else if (mode == 2) {
        int base = rnd.next(2, 40);
        n = rnd.next(3, 22);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 70) {
                int power = rnd.next(0, 5);
                int value = 1;
                for (int j = 0; j < power; ++j) value = clampValue(1LL * value * base);
                a.push_back(value);
            } else {
                a.push_back(rnd.next(1, 120));
            }
        }
    } else if (mode == 3) {
        vector<int> choices = {1, 2, 4, 5, 8, 10, 16, 20, 25, 40, 50, 100,
                               2000000, 1000000, 500000, 250000, 125000};
        n = rnd.next(2, 20);
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(choices));
    } else if (mode == 4) {
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29,
                              31, 37, 41, 43, 47, 53, 59, 61};
        n = rnd.next(2, (int)primes.size());
        shuffle(primes.begin(), primes.end());
        for (int i = 0; i < n; ++i) {
            int value = primes[i];
            if (rnd.next(0, 99) < 35) value *= rnd.any(vector<int>{1, 2, 3, 5});
            a.push_back(clampValue(value));
        }
    } else {
        n = rnd.next(2, 24);
        int low = rnd.next(1, 80);
        int high = rnd.next(low, min(200, low + rnd.next(0, 120)));
        for (int i = 0; i < n; ++i) a.push_back(rnd.next(low, high));
    }

    shuffle(a.begin(), a.end());

    println((int)a.size());
    println(a);
    return 0;
}
