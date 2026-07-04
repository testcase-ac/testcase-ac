#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct Case {
    int n;
    int m;
    int p;
    int x;
    int a;
    int b;
    int c;
};

int randBelow(int p) {
    return rnd.next(0, p - 1);
}

Case makeCase(int mode) {
    Case tc{};

    if (mode == 0) {
        tc.n = rnd.next(1, 8);
        tc.m = rnd.next(1, 8);
        tc.p = 1;
        tc.x = tc.a = tc.b = tc.c = 0;
        return tc;
    }

    if (mode == 1) {
        tc.n = rnd.next(1, 12);
        tc.m = rnd.next(1, 12);
        tc.p = rnd.next(2, 9);
        tc.x = randBelow(tc.p);
        tc.a = 0;
        tc.b = rnd.next(0, 1) ? 0 : 1;
        tc.c = randBelow(tc.p);
        return tc;
    }

    if (mode == 2) {
        tc.n = rnd.next(1, 20);
        tc.m = rnd.next(1, 20);
        tc.p = rnd.next(2, 200);
        tc.x = randBelow(tc.p);
        tc.a = randBelow(tc.p);
        tc.b = randBelow(tc.p);
        tc.c = randBelow(tc.p);
        return tc;
    }

    if (mode == 3) {
        tc.n = rnd.next(20, 80);
        tc.m = rnd.next(20, 80);
        tc.p = rnd.next(2, 30);
        tc.x = randBelow(tc.p);
        tc.a = randBelow(tc.p);
        tc.b = randBelow(tc.p);
        tc.c = randBelow(tc.p);
        return tc;
    }

    tc.n = rnd.next(1, 40);
    tc.m = rnd.next(1, 40);
    tc.p = rnd.next(900000000, 1000000000);
    tc.x = randBelow(tc.p);
    tc.a = randBelow(tc.p);
    tc.b = randBelow(tc.p);
    tc.c = randBelow(tc.p);
    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 12);
    vector<Case> cases;
    cases.reserve(t);

    for (int i = 0; i < t; ++i) {
        int mode = rnd.next(0, 4);
        if (i == 0) mode = rnd.next(0, 1);
        cases.push_back(makeCase(mode));
    }

    println(t);
    for (const Case& tc : cases) {
        println(tc.n, tc.m, tc.p, tc.x, tc.a, tc.b, tc.c);
    }

    return 0;
}
