#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_A = 1000000000;

int randomOddCoprime(int p) {
    while (true) {
        int x = rnd.next(2, 200000);
        if (x % p != 0) return x;
    }
}

int multipleOf(int p) {
    int limit = MAX_A / p;
    return p * rnd.next(1, limit);
}

int notMultipleOf(int p) {
    while (true) {
        int x = rnd.next(2, MAX_A);
        if (x % p != 0) return x;
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 99991};
    int mode = rnd.next(0, 5);
    int n;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(3, 12);
        int p = rnd.any(primes);
        int need = (n + 1) / 2;
        for (int i = 0; i < need; ++i) a.push_back(multipleOf(p));
        while ((int)a.size() < n) a.push_back(notMultipleOf(p));
    } else if (mode == 1) {
        n = rnd.next(3, 15);
        int p = rnd.any(primes);
        int count = max(1, (n + 1) / 2 - 1);
        for (int i = 0; i < count; ++i) a.push_back(multipleOf(p));
        while ((int)a.size() < n) a.push_back(notMultipleOf(p));
    } else if (mode == 2) {
        n = rnd.next(3, 20);
        int p = rnd.any(primes);
        int value = multipleOf(p);
        int count = rnd.next((n + 1) / 2, n);
        for (int i = 0; i < count; ++i) a.push_back(value);
        while ((int)a.size() < n) a.push_back(notMultipleOf(p));
    } else if (mode == 3) {
        n = rnd.next(3, 18);
        for (int i = 0; i < n; ++i) {
            if (i % 3 == 0) a.push_back(rnd.next(999999900, MAX_A));
            else a.push_back(rnd.next(2, 200));
        }
    } else if (mode == 4) {
        n = rnd.next(3, 21);
        vector<int> factors = {2, 3, 5};
        for (int i = 0; i < n; ++i) {
            int p = rnd.any(factors);
            a.push_back(multipleOf(p));
        }
    } else {
        n = rnd.next(3, 14);
        int base = rnd.next(2, 1000);
        for (int i = 0; i < n; ++i) {
            int x = base + rnd.next(0, 20);
            a.push_back(max(2, x));
        }
    }

    shuffle(a.begin(), a.end());
    println(n);
    println(a);

    return 0;
}
