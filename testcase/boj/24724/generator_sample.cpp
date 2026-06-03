#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

struct CaseData {
    int n;
    long long a;
    long long b;
    vector<pair<long long, long long>> parts;
};

long long chooseBound(int mode, bool sizeBound) {
    if (mode == 0) return 1;
    if (mode == 1) return 1000000000LL;
    if (mode == 2) return sizeBound ? rnd.next(1, 8) : rnd.next(1, 12);
    if (mode == 3) return rnd.next(1, 1000);
    return rnd.next(1, 1000000000);
}

long long chooseValue(long long limit, int style) {
    if (limit == 1) return 1;
    if (style == 0) return 1;
    if (style == 1) return limit;
    if (style == 2) return rnd.next(1LL, min(limit, 10LL));
    if (style == 3) return rnd.next(max(1LL, limit - 9), limit);
    return rnd.next(1LL, limit);
}

CaseData makeCase(int mode) {
    CaseData tc;

    if (mode == 0) {
        tc.n = 1;
        tc.a = 1;
        tc.b = 1;
    } else if (mode == 1) {
        tc.n = rnd.next(1, 4);
        tc.a = 1000000000LL;
        tc.b = 1000000000LL;
    } else {
        tc.n = rnd.next(1, mode == 4 ? 12 : 6);
        tc.a = chooseBound(mode, true);
        tc.b = chooseBound(mode, false);
    }

    int style = rnd.next(0, 4);
    tc.parts.reserve(tc.n);
    for (int i = 0; i < tc.n; ++i) {
        int localStyle = (style + i + rnd.next(0, 2)) % 5;
        tc.parts.push_back({chooseValue(tc.a, localStyle), chooseValue(tc.b, 4 - localStyle)});
    }

    if (mode == 4) {
        shuffle(tc.parts.begin(), tc.parts.end());
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    vector<CaseData> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = i < 2 ? i : rnd.next(0, 4);
        cases.push_back(makeCase(mode));
    }

    println(t);
    for (const CaseData& tc : cases) {
        println(tc.n);
        println(tc.a, tc.b);
        for (const auto& part : tc.parts) {
            println(part.first, part.second);
        }
    }

    return 0;
}
