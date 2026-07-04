#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

struct CaseData {
    int n;
    int w;
    vector<int> outer;
    vector<int> inner;
};

int nearHalf(int w, int delta) {
    int base = max(1, w / 2);
    return min(w, max(1, base + delta));
}

int pairFriendlyValue(int w) {
    return rnd.next(1, max(1, w / 2));
}

int pairBlockingValue(int w) {
    if (w == 1) return 1;
    return rnd.next(w / 2 + 1, w);
}

CaseData makeCase(int mode) {
    CaseData tc;
    tc.n = rnd.next(1, 14);
    if (mode == 5) tc.n = rnd.next(18, 60);
    tc.w = rnd.next(1, 10000);
    tc.outer.assign(tc.n, 1);
    tc.inner.assign(tc.n, 1);

    if (mode == 0) {
        for (int i = 0; i < tc.n; ++i) {
            tc.outer[i] = rnd.next(1, tc.w);
            tc.inner[i] = rnd.next(1, tc.w);
        }
    } else if (mode == 1) {
        for (int i = 0; i < tc.n; ++i) {
            tc.outer[i] = pairFriendlyValue(tc.w);
            tc.inner[i] = pairFriendlyValue(tc.w);
        }
    } else if (mode == 2) {
        for (int i = 0; i < tc.n; ++i) {
            tc.outer[i] = pairBlockingValue(tc.w);
            tc.inner[i] = pairBlockingValue(tc.w);
        }
    } else if (mode == 3) {
        for (int i = 0; i < tc.n; ++i) {
            int delta = rnd.next(-2, 2);
            tc.outer[i] = nearHalf(tc.w, delta);
            tc.inner[i] = nearHalf(tc.w, -delta);
            if (rnd.next(0, 3) == 0) swap(tc.outer[i], tc.inner[i]);
        }
    } else if (mode == 4) {
        for (int i = 0; i < tc.n; ++i) {
            bool even = i % 2 == 0;
            tc.outer[i] = even ? pairFriendlyValue(tc.w) : pairBlockingValue(tc.w);
            tc.inner[i] = even ? pairBlockingValue(tc.w) : pairFriendlyValue(tc.w);
        }
    } else {
        int low = rnd.next(1, max(1, tc.w / 3));
        int high = rnd.next(max(1, tc.w * 2 / 3), tc.w);
        for (int i = 0; i < tc.n; ++i) {
            tc.outer[i] = (i % 3 == 0) ? high : rnd.next(1, tc.w);
            tc.inner[i] = (i % 3 == 1) ? high : rnd.next(low, tc.w);
        }
    }

    if (tc.n > 1 && mode != 0) {
        if (rnd.next(0, 1) == 0) {
            tc.outer[0] = pairFriendlyValue(tc.w);
            tc.outer[tc.n - 1] = pairFriendlyValue(tc.w);
        } else {
            tc.outer[0] = pairBlockingValue(tc.w);
            tc.outer[tc.n - 1] = pairBlockingValue(tc.w);
        }
        if (rnd.next(0, 1) == 0) {
            tc.inner[0] = pairFriendlyValue(tc.w);
            tc.inner[tc.n - 1] = pairFriendlyValue(tc.w);
        } else {
            tc.inner[0] = pairBlockingValue(tc.w);
            tc.inner[tc.n - 1] = pairBlockingValue(tc.w);
        }
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    vector<CaseData> cases;
    for (int i = 0; i < t; ++i) {
        cases.push_back(makeCase(rnd.next(0, 5)));
    }

    println(t);
    for (const CaseData& tc : cases) {
        println(tc.n, tc.w);
        println(tc.outer);
        println(tc.inner);
    }

    return 0;
}
