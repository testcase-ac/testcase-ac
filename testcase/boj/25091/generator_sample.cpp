#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

struct TestCase {
    vector<int> fun;
    vector<int> parent;
};

int funValue(int mode) {
    if (mode == 0) return rnd.next(1, 20);
    if (mode == 1) return rnd.next(1, 2) == 1 ? 1 : 1000000000;
    if (mode == 2) return rnd.next(900000000, 1000000000);
    return rnd.next(1, 1000000000);
}

TestCase makeCase(int mode) {
    int n = rnd.next(1, 16);
    TestCase tc;
    tc.fun.assign(n, 0);
    tc.parent.assign(n, 0);

    int funMode = rnd.next(0, 3);
    for (int i = 0; i < n; ++i) {
        tc.fun[i] = funValue(funMode);
    }

    if (mode == 0) {
        for (int i = 1; i < n; ++i) tc.parent[i] = i;
    } else if (mode == 1) {
        for (int i = 1; i < n; ++i) tc.parent[i] = 1;
    } else if (mode == 2) {
        for (int i = 1; i < n; ++i) tc.parent[i] = (i + 1) / 2;
    } else if (mode == 3) {
        int roots = rnd.next(1, min(n, 5));
        for (int i = roots; i < n; ++i) tc.parent[i] = rnd.next(1, i);
    } else {
        for (int i = 1; i < n; ++i) {
            if (rnd.next(0, 99) < 25) {
                tc.parent[i] = 0;
            } else if (rnd.next(0, 99) < 45) {
                tc.parent[i] = rnd.next(max(1, i - 3), i);
            } else {
                tc.parent[i] = rnd.next(1, i);
            }
        }
    }

    return tc;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);
    for (int tc = 0; tc < t; ++tc) {
        TestCase cur = makeCase(rnd.next(0, 4));
        println((int)cur.fun.size());
        println(cur.fun);
        println(cur.parent);
    }

    return 0;
}
