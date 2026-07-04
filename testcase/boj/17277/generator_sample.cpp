#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct CaseData {
    int n;
    long long X;
    long long y;
    long long Z;
    vector<int> values;
};

static CaseData makeCase(int mode) {
    CaseData tc;

    if (mode == 0) {
        tc.n = 1;
        tc.y = rnd.next(0, 5);
        tc.X = rnd.next(0, 10);
        tc.Z = rnd.next(0, 5);
        tc.values = {rnd.next(-5, 10)};
        return tc;
    }

    if (mode == 1) {
        tc.n = rnd.next(2, 8);
        tc.y = 0;
        tc.X = 0;
        tc.Z = rnd.next(0, 12);
        tc.values.resize(tc.n);
        for (int& v : tc.values) {
            v = rnd.next(-8, 8);
        }
        return tc;
    }

    if (mode == 2) {
        tc.n = rnd.next(2, 10);
        tc.y = rnd.next(1, 7);
        tc.X = rnd.next(0LL, tc.y - 1);
        tc.Z = rnd.next(0, 20);
        tc.values.resize(tc.n);
        for (int& v : tc.values) {
            v = rnd.next(0, 20);
        }
        return tc;
    }

    if (mode == 3) {
        tc.n = rnd.next(3, 12);
        tc.y = rnd.next(0, 5);
        tc.X = tc.y == 0 ? rnd.next(0, 20) : 1LL * tc.y * rnd.next(1, min(tc.n, 5));
        tc.Z = rnd.next(0, 10);
        tc.values.assign(tc.n, rnd.next(-4, 4));
        int pos = rnd.next(0, tc.n - 1);
        tc.values[pos] = (int)(tc.y + tc.Z + rnd.next(0, 4));
        return tc;
    }

    if (mode == 4) {
        tc.n = rnd.next(5, 15);
        tc.y = rnd.next(1, 6);
        int maxLen = rnd.next(2, min(tc.n, 6));
        tc.X = 1LL * tc.y * maxLen;
        tc.Z = rnd.next(4, 16);
        tc.values.assign(tc.n, -rnd.next(1, 8));
        int len = rnd.next(2, maxLen);
        int start = rnd.next(0, tc.n - len);
        for (int i = 0; i < len; ++i) {
            tc.values[start + i] = (int)(tc.y + rnd.next(1, 5));
        }
        return tc;
    }

    if (mode == 5) {
        tc.n = rnd.next(8, 20);
        tc.y = rnd.next(0, 20);
        int budgetDays = rnd.next(1, min(tc.n, 10));
        tc.X = tc.y == 0 ? rnd.next(0LL, 100LL) : 1LL * tc.y * budgetDays + rnd.next(0LL, tc.y - 1);
        tc.Z = rnd.next(0, 60);
        tc.values.resize(tc.n);
        for (int i = 0; i < tc.n; ++i) {
            int base = (i % 2 == 0) ? rnd.next(-20, 5) : rnd.next(0, 30);
            tc.values[i] = base;
        }
        shuffle(tc.values.begin(), tc.values.end());
        return tc;
    }

    tc.n = rnd.next(1, 20);
    tc.y = rnd.any(vector<long long>{0LL, 1LL, 1000000000LL, rnd.next(0, 1000)});
    tc.X = rnd.any(vector<long long>{0LL, 1LL, 1000000000LL, rnd.next(0, 5000)});
    tc.Z = rnd.any(vector<long long>{0LL, 1LL, 1000000000LL, rnd.next(0, 5000)});
    tc.values.resize(tc.n);
    for (int& v : tc.values) {
        v = rnd.any(vector<int>{-1000000, -1, 0, 1, 1000000, rnd.next(-100, 100)});
    }
    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 10);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        CaseData data = makeCase(rnd.next(0, 6));
        println(data.n, data.X, data.y, data.Z);
        println(data.values);
    }

    return 0;
}
