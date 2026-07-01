#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Case {
    int n;
    int m;
    int a;
};

int randomAreaAtMost(int limit) {
    vector<int> special = {1, limit};
    if (limit > 1) special.push_back(limit - 1);
    if (limit >= 2) special.push_back(2);
    if (limit >= 3) special.push_back(3);
    if (limit >= 10) special.push_back(rnd.next(1, min(limit, 10)));
    special.push_back(rnd.next(1, limit));
    return rnd.any(special);
}

Case makeCase(int mode) {
    int n;
    int m;
    long long areaLimit;

    switch (mode) {
        case 0:
            n = rnd.next(1, 4);
            m = rnd.next(1, 4);
            break;
        case 1:
            n = rnd.any(vector<int>{1, 2, 9999, 10000});
            m = rnd.next(1, 10000);
            break;
        case 2:
            n = rnd.next(1, 10000);
            m = rnd.any(vector<int>{1, 2, 9999, 10000});
            break;
        case 3:
            n = rnd.next(9990, 10000);
            m = rnd.next(9990, 10000);
            break;
        default:
            n = rnd.next(1, 10000);
            m = rnd.next(1, 10000);
            break;
    }

    areaLimit = 1LL * n * m;

    bool forcePossible = rnd.next(2) == 0;
    if (mode == 4) forcePossible = false;
    if (areaLimit >= 100000000LL) forcePossible = true;

    int a;
    if (forcePossible) {
        a = randomAreaAtMost((int)min(areaLimit, 100000000LL));
    } else {
        int lo = (int)min(areaLimit + 1, 100000000LL);
        if (lo > 100000000) {
            a = randomAreaAtMost((int)min(areaLimit, 100000000LL));
        } else {
            a = rnd.next(lo, 100000000);
        }
    }

    return {n, m, a};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int c = rnd.next(1, 30);
    vector<Case> cases;
    cases.reserve(c);

    for (int i = 0; i < c; ++i) {
        int mode = rnd.next(0, 5);
        cases.push_back(makeCase(mode));
    }

    println(c);
    for (const Case& tc : cases) {
        println(tc.n, tc.m, tc.a);
    }

    return 0;
}
