#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Case {
    int n;
    long long r;
    long long s;
    long long e;
};

long long limitFor(int n) {
    return (1LL << n) - 1;
}

long long randomIndex(int n) {
    if (n == 0) return 0;
    if (rnd.next(4) == 0) return rnd.next(0LL, min(20LL, limitFor(n)));
    if (rnd.next(4) == 0) return limitFor(n) - rnd.next(0LL, min(20LL, limitFor(n)));
    return rnd.next(0LL, limitFor(n));
}

Case makeCase(int mode) {
    int n = 0;
    if (mode == 0) {
        n = rnd.next(0, 6);
    } else if (mode == 1) {
        n = rnd.next(7, 20);
    } else if (mode == 2) {
        n = rnd.next(45, 60);
    } else {
        n = rnd.any(vector<int>{0, 1, 2, 3, 10, 20, 48, 59, 60});
    }

    long long limit = limitFor(n);
    long long r = randomIndex(n);
    long long s = 0;
    long long width = 0;

    if (mode == 0) {
        s = rnd.next(0LL, limit);
        width = rnd.next(0LL, min(10LL, limit - s));
    } else if (mode == 1) {
        width = rnd.next(0LL, min(10000LL, limit));
        s = rnd.next(0LL, limit - width);
    } else if (mode == 2) {
        width = rnd.next(0LL, 10000LL);
        long long anchor = rnd.next(0LL, min(20000LL, limit));
        if (rnd.next(2) == 0) {
            s = min(anchor, limit - width);
        } else {
            s = limit - width - min(anchor, limit - width);
        }
    } else {
        width = rnd.any(vector<long long>{0, 1, 2, 10, 9999, 10000});
        width = min(width, limit);
        s = rnd.next(0LL, limit - width);
    }

    return {n, r, s, s + width};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(5, 18);
    vector<Case> cases;
    cases.reserve(testCount);

    for (int i = 0; i < testCount; ++i) {
        cases.push_back(makeCase(rnd.next(0, 3)));
    }

    shuffle(cases.begin(), cases.end());
    for (const Case& tc : cases) {
        println(tc.n, tc.r, tc.s, tc.e);
    }
    println(-1, -1, -1, -1);

    return 0;
}
