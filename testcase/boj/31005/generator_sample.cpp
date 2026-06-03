#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

long long randomSmallValue(long long limit) {
    return rnd.next(1LL, limit);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long MAX_M = 1000000000000000000LL;
    const long long MAX_A = 1000000000000LL;

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 20);
    long long m = 1;
    vector<long long> a(n);

    if (mode == 0) {
        m = rnd.next(1LL, 80LL);
        for (long long& x : a) {
            x = randomSmallValue(25);
        }
    } else if (mode == 1) {
        long long base = rnd.next(1LL, 20LL);
        m = base * rnd.next(1LL, 30LL) + rnd.next(0LL, base);
        for (long long& x : a) {
            x = base + rnd.next(-min(base - 1, 3LL), 5LL);
        }
    } else if (mode == 2) {
        m = rnd.next(1LL, 1000LL);
        for (long long& x : a) {
            x = rnd.next(m + 1, min(MAX_A, m + 1000));
        }
    } else if (mode == 3) {
        m = rnd.next(MAX_M - 1000000LL, MAX_M);
        for (long long& x : a) {
            x = rnd.next(MAX_A - 1000LL, MAX_A);
        }
    } else if (mode == 4) {
        n = rnd.next(18, 45);
        a.assign(n, 1);
        m = rnd.next(1LL, 200LL);
        for (long long& x : a) {
            int pick = rnd.next(0, 3);
            if (pick == 0) x = 1;
            if (pick == 1) x = rnd.next(2LL, 12LL);
            if (pick == 2) x = rnd.next(50LL, 200LL);
        }
    } else {
        n = rnd.next(1, 35);
        a.assign(n, 1);
        m = rnd.any(vector<long long>{1LL, 2LL, 999999999999LL, MAX_A, MAX_M});
        for (long long& x : a) {
            int pick = rnd.next(0, 4);
            if (pick == 0) x = 1;
            if (pick == 1) x = rnd.next(2LL, 100LL);
            if (pick == 2) x = rnd.next(999999999900LL, MAX_A);
            if (pick == 3) x = m <= MAX_A ? m : rnd.next(1LL, MAX_A);
        }
    }

    if (rnd.next(0, 1)) {
        shuffle(a.begin(), a.end());
    }

    println(n, m);
    println(a);

    return 0;
}
