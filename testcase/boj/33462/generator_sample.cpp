#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long LIMIT = 1000000000LL;
    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 16);
    long long xLimit = (mode == 5 ? LIMIT : rnd.next(2, 80));
    long long X = xLimit;
    long long D = rnd.next(1LL, min(X + 20, LIMIT));
    vector<long long> x(n), y(n);

    if (mode == 0) {
        X = rnd.next(2LL, 40LL);
        D = rnd.next(X, min(X + 20, LIMIT));
        for (int i = 0; i < n; ++i) {
            x[i] = rnd.next(1LL, X - 1);
            y[i] = rnd.next(1LL, 20LL);
        }
    } else if (mode == 1) {
        X = rnd.next(20LL, 90LL);
        D = rnd.next(1LL, min(8LL, X - 1));
        for (int i = 0; i < n; ++i) {
            x[i] = rnd.next(D + 1, X - 1);
            y[i] = rnd.next(1LL, 10LL);
        }
    } else if (mode == 2) {
        X = rnd.next(10LL, 70LL);
        D = rnd.next(1LL, X - 1);
        long long shared = rnd.next(1LL, X - 1);
        for (int i = 0; i < n; ++i) {
            x[i] = (rnd.next(0, 2) == 0 ? shared : rnd.next(1LL, X - 1));
            y[i] = rnd.next(1LL, 25LL);
        }
    } else if (mode == 3) {
        X = rnd.next(8LL, 80LL);
        D = rnd.next(1LL, X - 1);
        long long pos = rnd.next(1LL, min(D, X - 1));
        for (int i = 0; i < n; ++i) {
            pos = min(X - 1, pos + rnd.next(0LL, 7LL));
            x[i] = pos;
            y[i] = rnd.next(1LL, 18LL);
        }
        shuffle(x.begin(), x.end());
    } else if (mode == 4) {
        X = rnd.next(12LL, 100LL);
        D = rnd.next(1LL, X - 1);
        for (int i = 0; i < n; ++i) {
            x[i] = rnd.next(1LL, X - 1);
            y[i] = rnd.next(1LL, 4LL);
        }
        int boost = rnd.next(0, n - 1);
        x[boost] = rnd.next(1LL, min(D, X - 1));
        y[boost] = rnd.next(X, min(X + 40, LIMIT));
    } else {
        X = LIMIT;
        D = rnd.next(1LL, LIMIT);
        for (int i = 0; i < n; ++i) {
            x[i] = rnd.next(1LL, X - 1);
            y[i] = rnd.next(max(1LL, LIMIT - 200LL), LIMIT);
        }
    }

    println(n, D, X);
    println(x);
    println(y);

    return 0;
}
