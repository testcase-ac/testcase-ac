#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct CaseData {
    int n;
    int m;
    long long x;
    long long y;
    long long z;
    vector<long long> a;
};

CaseData makeCase(int mode) {
    CaseData tc;

    if (mode == 0) {
        tc.n = rnd.next(1, 4);
        tc.m = 1;
        tc.x = rnd.next(0, 2);
        tc.y = rnd.next(0, 2);
        tc.z = 1;
        tc.a = {0};
        return tc;
    }

    if (mode == 1) {
        tc.n = rnd.next(3, 18);
        tc.m = tc.n;
        tc.x = 0;
        tc.y = 0;
        tc.z = rnd.next(2, 40);
        tc.a.resize(tc.m);
        for (int i = 0; i < tc.m; ++i) tc.a[i] = rnd.next(0LL, tc.z - 1);
        return tc;
    }

    if (mode == 2) {
        tc.n = rnd.next(8, 35);
        tc.m = rnd.next(1, min(8, tc.n));
        tc.x = rnd.next(0LL, 20LL);
        tc.y = rnd.next(0LL, 20LL);
        tc.z = rnd.next(2LL, 60LL);
        tc.a.resize(tc.m);
        for (int i = 0; i < tc.m; ++i) tc.a[i] = rnd.next(0LL, tc.z - 1);
        return tc;
    }

    if (mode == 3) {
        tc.n = rnd.next(10, 45);
        tc.m = rnd.next(2, min(10, tc.n));
        tc.x = rnd.any(vector<long long>{0, 1, 2, 1000000000LL});
        tc.y = rnd.any(vector<long long>{0, 1, 3, 1000000000LL});
        tc.z = rnd.any(vector<long long>{2, 3, 5, 7, 1000000000LL});
        tc.a.resize(tc.m);
        for (int i = 0; i < tc.m; ++i) {
            if (rnd.next(2) == 0) {
                tc.a[i] = 0;
            } else {
                tc.a[i] = rnd.next(0LL, min(9LL, tc.z - 1));
            }
        }
        return tc;
    }

    tc.n = rnd.next(80, 180);
    tc.m = rnd.next(1, min(100, tc.n));
    tc.x = rnd.next(0LL, 1000000000LL);
    tc.y = rnd.next(0LL, 1000000000LL);
    tc.z = rnd.next(2LL, 1000000000LL);
    tc.a.resize(tc.m);
    for (int i = 0; i < tc.m; ++i) tc.a[i] = rnd.next(0LL, tc.z - 1);
    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int cases = rnd.next(4, 10);
    println(cases);

    for (int tc = 0; tc < cases; ++tc) {
        int mode = tc < 5 ? tc : rnd.next(0, 4);
        CaseData data = makeCase(mode);

        println(data.n, data.m, data.x, data.y, data.z);
        for (long long value : data.a) println(value);
    }

    return 0;
}
