#include "testlib.h"

#include <vector>
using namespace std;

const int MAX_COEF = 1000000006;

int randomCoefficient(int profile) {
    if (profile == 0) return rnd.next(0, 9);
    if (profile == 1) return rnd.next(0, 1000);
    if (profile == 2) return rnd.any(vector<int>{0, 1, 2, MAX_COEF - 1, MAX_COEF});
    return rnd.next(0, MAX_COEF);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = 0;
    } else if (mode == 1) {
        n = rnd.next(1, 3);
    } else if (mode == 2) {
        n = rnd.next(4, 20);
    } else if (mode == 3) {
        n = rnd.next(21, 80);
    } else if (mode == 4) {
        n = rnd.next(81, 400);
    } else if (mode == 5) {
        n = rnd.next(401, 1200);
    } else {
        n = rnd.any(vector<int>{3998, 3999, 4000});
    }

    int profile = rnd.next(0, 3);
    vector<int> f(n + 1);

    if (mode >= 4 && rnd.next(0, 1) == 0) {
        int nonzeroCount = rnd.next(1, min(n + 1, 12));
        for (int i = 0; i < nonzeroCount; ++i) {
            int pos = rnd.next(0, n);
            f[pos] = randomCoefficient(profile);
            if (f[pos] == 0) f[pos] = rnd.next(1, MAX_COEF);
        }
    } else {
        for (int i = 0; i <= n; ++i) {
            f[i] = randomCoefficient(profile);
        }
    }

    if (n >= 1 && f[n] == 0) {
        f[n] = randomCoefficient(profile);
        if (f[n] == 0) f[n] = 1;
    }

    println(n);
    println(f);

    return 0;
}
