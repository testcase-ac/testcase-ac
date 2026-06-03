#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const int MAXV = 1000000000;

int boundedProduct(int a, int b) {
    return (int)min(1LL * a * b, 1LL * MAXV);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int A = 1;
    int B = 1;

    if (mode == 0) {
        A = rnd.next(1, 1000);
        int q = rnd.next(1, MAXV / A);
        B = A * q;
    } else if (mode == 1) {
        A = rnd.next(2, MAXV);
        B = rnd.next(1, A - 1);
    } else if (mode == 2) {
        int g = rnd.next(1, 100000);
        int x = rnd.next(1, MAXV / g);
        int y = rnd.next(1, MAXV / g);
        if (x == y) y = y == MAXV / g ? 1 : y + 1;
        A = boundedProduct(g, x);
        B = boundedProduct(g, y);
    } else if (mode == 3) {
        vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};
        shuffle(primes.begin(), primes.end());
        A = 1;
        B = 1;
        int factors = rnd.next(1, 6);
        for (int i = 0; i < factors; ++i) {
            int p = primes[i];
            int ea = rnd.next(0, 5);
            int eb = rnd.next(0, 5);
            for (int j = 0; j < ea && A <= MAXV / p; ++j) A *= p;
            for (int j = 0; j < eb && B <= MAXV / p; ++j) B *= p;
        }
    } else if (mode == 4) {
        A = rnd.next(MAXV - 1000000, MAXV);
        B = rnd.next(MAXV - 1000000, MAXV);
    } else {
        int base = rnd.next(1, 31623);
        A = base * base;
        int multiplier = rnd.next(1, MAXV / A);
        B = A * multiplier;
    }

    println(A, B);
    return 0;
}
