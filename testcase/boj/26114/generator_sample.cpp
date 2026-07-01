#include "testlib.h"

#include <vector>

using namespace std;

const long long LIM = 10000000000000000LL;

long long randomLarge() {
    int mode = rnd.next(0, 3);
    if (mode == 0) return LIM;
    if (mode == 1) return LIM - rnd.next(0, 1000);
    if (mode == 2) return rnd.next(1000000LL, 1000000000000LL);
    return rnd.next(0LL, LIM);
}

vector<long long> makeFrequencies(int n, int mode) {
    vector<long long> f(n);

    if (mode == 0) {
        return f;
    }

    if (mode == 1) {
        for (long long& x : f) x = rnd.next(0, 1);
        return f;
    }

    if (mode == 2) {
        for (long long& x : f) x = rnd.next(0, 6);
        return f;
    }

    if (mode == 3) {
        int pos = rnd.next(0, n - 1);
        f[pos] = rnd.next(0, 1) ? randomLarge() : rnd.next(1LL, 2000LL);
        return f;
    }

    if (mode == 4) {
        for (long long& x : f) x = rnd.next(0, 2000);
        return f;
    }

    if (mode == 5) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 70) {
                f[i] = rnd.next(0, 5);
            } else {
                f[i] = randomLarge();
            }
        }
        return f;
    }

    for (int i = 0; i < n; ++i) {
        if (i % 3 == 0) f[i] = 0;
        else if (i % 3 == 1) f[i] = 1;
        else f[i] = rnd.next(2LL, 20LL);
    }
    return f;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 20);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == 0 && rnd.next(0, 3) == 0) {
            n = 1;
        } else if (tc == t - 1 && rnd.next(0, 3) == 0) {
            n = 50;
        } else {
            n = rnd.next(1, 15);
        }

        int mode = rnd.next(0, 6);
        vector<long long> f = makeFrequencies(n, mode);

        println(n);
        println(f);
    }

    return 0;
}
