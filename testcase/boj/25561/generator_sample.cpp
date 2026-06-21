#include "testlib.h"

#include <vector>

using namespace std;

static vector<long long> makeYesLike(int n) {
    vector<long long> c(n);
    if (n == 1) {
        c[0] = 2;
        return c;
    }

    c[n - 1] = rnd.next(1, 2);
    long long lb = 2;
    long long avail = c[n - 1] == 1 ? 3 : 4;

    for (int i = n - 2; i >= 1; --i) {
        c[i] = rnd.next(lb, avail);
        lb = c[i];
        avail = (avail - c[i]) + 2 * c[i];
    }

    c[0] = avail;
    return c;
}

static vector<long long> makeRandomCounts(int n) {
    vector<long long> c(n);
    int mode = rnd.next(4);
    for (int i = 0; i < n; ++i) {
        if (mode == 0) {
            c[i] = rnd.next(1, 8);
        } else if (mode == 1) {
            c[i] = rnd.next(1, 50);
        } else if (mode == 2) {
            c[i] = rnd.next(999999900LL, 1000000000LL);
        } else {
            c[i] = rnd.next(1LL, 1000000000LL);
        }
    }
    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(4, 12);
    vector<vector<long long>> tests;
    tests.reserve(T);

    for (int tc = 0; tc < T; ++tc) {
        int n;
        if (tc == 0) {
            n = 1;
        } else if (rnd.next(100) < 75) {
            n = rnd.next(1, 8);
        } else {
            n = rnd.next(9, 25);
        }

        if (rnd.next(100) < 45) {
            tests.push_back(makeYesLike(n));
        } else {
            tests.push_back(makeRandomCounts(n));
        }
    }

    println((int)tests.size());
    for (const vector<long long>& c : tests) {
        println((int)c.size());
        println(c);
    }

    return 0;
}
