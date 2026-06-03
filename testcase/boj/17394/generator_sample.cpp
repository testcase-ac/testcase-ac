#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Case {
    int n;
    int a;
    int b;
};

vector<int> buildPrimes() {
    vector<bool> isPrime(100001, true);
    isPrime[0] = isPrime[1] = false;
    for (int i = 2; i * i <= 100000; ++i) {
        if (!isPrime[i]) continue;
        for (int j = i * i; j <= 100000; j += i) isPrime[j] = false;
    }

    vector<int> primes;
    for (int i = 2; i <= 100000; ++i) {
        if (isPrime[i]) primes.push_back(i);
    }
    return primes;
}

int randomComposite() {
    static const vector<int> values = {
        4, 6, 8, 9, 10, 12, 14, 15, 16, 18, 20, 21, 25, 27, 49, 121,
        99990, 99992, 99993, 99994, 99995, 99996, 99998, 99999, 100000};
    return rnd.any(values);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> primes = buildPrimes();
    vector<Case> cases;
    int t = rnd.next(6, 10);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 6);
        int n, a, b;

        if (mode == 0) {
            int p = rnd.any(primes);
            n = p;
            a = max(2, p - rnd.next(0, 2));
            b = min(100000, p + rnd.next(0, 2));
        } else if (mode == 1) {
            int c = randomComposite();
            n = rnd.next(2, 1000000);
            a = b = c;
        } else if (mode == 2) {
            int width = rnd.next(0, 8);
            a = rnd.next(2, 100000 - width);
            b = a + width;
            n = rnd.next(2, 80);
        } else if (mode == 3) {
            a = rnd.next(2, 200);
            b = rnd.next(max(a, 99900), 100000);
            n = rnd.next(900000, 1000000);
        } else if (mode == 4) {
            a = rnd.any(primes);
            b = a;
            n = rnd.next(2, 1000000);
        } else if (mode == 5) {
            n = rnd.next(999900, 1000000);
            a = rnd.next(99950, 100000);
            b = rnd.next(a, 100000);
        } else {
            n = rnd.next(2, 1000000);
            a = rnd.next(2, 99991);
            b = min(100000, a + rnd.next(0, 100));
        }

        cases.push_back({n, a, b});
    }

    println(t);
    for (const Case& test : cases) println(test.n, test.a, test.b);

    return 0;
}
