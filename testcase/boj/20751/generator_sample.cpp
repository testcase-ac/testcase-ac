#include "testlib.h"

#include <cstdlib>
#include <vector>

using namespace std;

struct Case {
    long long n;
    long long m;
    long long r;
    long long c;
    long long s;
};

long long dist(long long a, long long b, long long c, long long d) {
    return llabs(a - c) + llabs(b - d);
}

bool valid(const Case& tc) {
    return 1 <= tc.r && tc.r <= tc.n && 1 <= tc.c && tc.c <= tc.m &&
           1 <= tc.s && tc.s <= 1000000000LL &&
           dist(tc.r, tc.c, 1, 1) > tc.s &&
           dist(tc.r, tc.c, tc.n, tc.m) > tc.s;
}

bool tuzikWins(const Case& tc) {
    bool rowFilled = tc.r - tc.s <= 1 && tc.r + tc.s >= tc.n;
    bool colFilled = tc.c - tc.s <= 1 && tc.c + tc.s >= tc.m;
    bool topLeftSealed = tc.r - tc.s <= 1 && tc.c - tc.s <= 1;
    bool bottomRightSealed = tc.r + tc.s >= tc.n && tc.c + tc.s >= tc.m;
    return rowFilled || colFilled || topLeftSealed || bottomRightSealed;
}

long long coordNear(long long lo, long long hi) {
    if (hi - lo <= 6) return rnd.next(lo, hi);
    if (rnd.next(2) == 0) return rnd.next(lo, lo + 3);
    return rnd.next(hi - 3, hi);
}

Case randomValidCase(bool wantTuzik) {
    for (int tries = 0; tries < 200000; ++tries) {
        long long n;
        long long m;
        if (rnd.next(5) == 0) {
            n = rnd.next(2LL, 1000000000LL);
            m = rnd.next(2LL, 1000000000LL);
        } else {
            n = rnd.next(2, 35);
            m = rnd.next(2, 35);
        }

        Case tc;
        tc.n = n;
        tc.m = m;
        tc.r = rnd.next(1LL, n);
        tc.c = rnd.next(1LL, m);
        long long maxS = min(1000000000LL,
                             min(dist(tc.r, tc.c, 1, 1),
                                 dist(tc.r, tc.c, n, m)) -
                                 1);
        if (maxS < 1) continue;

        if (rnd.next(3) == 0) {
            tc.s = rnd.next(1LL, maxS);
        } else {
            tc.s = coordNear(1, maxS);
        }

        if (valid(tc) && tuzikWins(tc) == wantTuzik) return tc;
    }

    if (wantTuzik) return {3, 3, 2, 2, 1};
    return {8, 4, 3, 3, 1};
}

Case rowBarrierCase() {
    long long n = rnd.next(3, 40);
    long long m = rnd.next(2, 40);
    for (int tries = 0; tries < 10000; ++tries) {
        Case tc = {n, m, rnd.next(2LL, n - 1), rnd.next(1LL, m), 1};
        long long need = max(tc.r - 1, n - tc.r);
        long long maxS = min(dist(tc.r, tc.c, 1, 1), dist(tc.r, tc.c, n, m)) - 1;
        if (need <= maxS) {
            tc.s = rnd.next(need, maxS);
            if (valid(tc) && tuzikWins(tc)) return tc;
        }
    }
    return randomValidCase(true);
}

Case colBarrierCase() {
    long long n = rnd.next(2, 40);
    long long m = rnd.next(3, 40);
    for (int tries = 0; tries < 10000; ++tries) {
        Case tc = {n, m, rnd.next(1LL, n), rnd.next(2LL, m - 1), 1};
        long long need = max(tc.c - 1, m - tc.c);
        long long maxS = min(dist(tc.r, tc.c, 1, 1), dist(tc.r, tc.c, n, m)) - 1;
        if (need <= maxS) {
            tc.s = rnd.next(need, maxS);
            if (valid(tc) && tuzikWins(tc)) return tc;
        }
    }
    return randomValidCase(true);
}

Case cornerSealCase(bool bottomRight) {
    for (int tries = 0; tries < 10000; ++tries) {
        long long n = rnd.next(3, 45);
        long long m = rnd.next(3, 45);
        Case tc = {n, m, rnd.next(1LL, n), rnd.next(1LL, m), 1};
        long long need = bottomRight ? max(n - tc.r, m - tc.c)
                                     : max(tc.r - 1, tc.c - 1);
        long long maxS = min(dist(tc.r, tc.c, 1, 1), dist(tc.r, tc.c, n, m)) - 1;
        if (need <= maxS) {
            tc.s = rnd.next(need, maxS);
            if (valid(tc) && tuzikWins(tc)) return tc;
        }
    }
    return randomValidCase(true);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(10, 24);
    vector<Case> cases;
    cases.push_back(rowBarrierCase());
    cases.push_back(colBarrierCase());
    cases.push_back(cornerSealCase(false));
    cases.push_back(cornerSealCase(true));
    cases.push_back({1000000000LL, 1000000000LL, 500000000LL, 500000000LL, 999999997LL});
    cases.push_back({1, 1000000000LL, 1, 500000000LL, 499999998LL});

    while ((int)cases.size() < t) {
        cases.push_back(randomValidCase(rnd.next(2) == 0));
    }
    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const Case& tc : cases) {
        println(tc.n, tc.m, tc.r, tc.c, tc.s);
    }

    return 0;
}
