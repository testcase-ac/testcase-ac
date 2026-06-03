#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int primeAt(int index) {
    static const vector<int> primes = {
        2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53,
        59, 61, 67, 71, 73, 79, 83, 89, 97
    };
    return primes[index % (int)primes.size()];
}

int compositeAt(int index) {
    static const vector<int> composites = {
        4, 6, 8, 9, 10, 12, 18, 24, 36, 49, 64, 72, 96, 121, 169, 1000000
    };
    return composites[index % (int)composites.size()];
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n = rnd.next(2, 30);
    vector<int> a(n);

    if (mode == 0) {
        int cur = rnd.next(1, 20);
        for (int i = 0; i < n; ++i) {
            cur += rnd.next(0, 12);
            a[i] = cur;
        }
    } else if (mode == 1) {
        int cur = rnd.next(100, 200);
        for (int i = 0; i < n; ++i) {
            cur -= rnd.next(0, 8);
            a[i] = max(1, cur);
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 3) == 0 ? 1 : primeAt(rnd.next(0, 24));
        }
        if (rnd.next(0, 1)) {
            shuffle(a.begin(), a.end());
        } else {
            sort(a.begin(), a.end());
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 4) == 0 ? primeAt(rnd.next(0, 24)) : compositeAt(rnd.next(0, 15));
        }
        shuffle(a.begin(), a.end());
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) {
            a[i] = i % 2 == 0 ? rnd.next(1, 12) : rnd.next(500000, 1000000);
        }
        if (rnd.next(0, 1)) {
            reverse(a.begin(), a.end());
        }
    } else if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(1, 1000000);
        }
    } else {
        n = rnd.next(2, 8);
        a.assign(n, 1);
        int pos = rnd.next(0, n - 1);
        a[pos] = rnd.next(0, 1) ? 1000000 : primeAt(rnd.next(0, 24));
        if (n > 2 && rnd.next(0, 1)) {
            a[rnd.next(0, n - 1)] = compositeAt(rnd.next(0, 15));
        }
    }

    println(n);
    println(a);

    return 0;
}
