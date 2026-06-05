#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

struct Case {
    long long a;
    long long b;
    long long c;
};

long long smallCount() {
    return rnd.next(0, 20);
}

long long largeCount() {
    return rnd.next(900000000LL, 1000000000LL);
}

Case makeCase(int mode) {
    if (mode == 0) {
        long long a = rnd.next(1, 20);
        long long c = rnd.next(0LL, a);
        long long b = smallCount();
        if ((a + 2 * b + 3 * c) % 2 != 0) ++b;
        return {a, b, c};
    }

    if (mode == 1) {
        long long a = smallCount();
        long long c = rnd.next(a + 1, a + 20);
        long long b = smallCount();
        return {a, b, c};
    }

    if (mode == 2) {
        long long b = rnd.next(0, 20) * 2 + 1;
        return {0, b, 0};
    }

    if (mode == 3) {
        long long a = smallCount();
        long long b = smallCount();
        long long c = smallCount();
        if (a + b + c == 0) a = 1;
        return {a, b, c};
    }

    if (mode == 4) {
        long long a = rnd.next(0, 1) ? largeCount() : smallCount();
        long long b = rnd.next(0, 1) ? largeCount() : smallCount();
        long long c = rnd.next(0, 1) ? largeCount() : smallCount();
        if (a + b + c == 0) b = 1;
        return {a, b, c};
    }

    long long x = rnd.next(0, 100);
    return {x, rnd.next(0, 100), x};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 30);
    vector<Case> cases;
    cases.reserve(t);

    vector<int> modes = {0, 1, 2, 3, 4, 5};
    for (int i = 0; i < t; ++i) {
        int mode = i < (int)modes.size() ? modes[i] : rnd.next(0, 5);
        cases.push_back(makeCase(mode));
    }
    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (const Case& tc : cases) {
        println(tc.a, tc.b, tc.c);
    }

    return 0;
}
