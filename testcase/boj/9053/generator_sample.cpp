#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

vector<int> makeCase(int mode) {
    int n;
    vector<int> t;

    if (mode == 0) {
        n = rnd.next(1, 3);
        int value = rnd.next(1, 10);
        t.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(8, 10);
        t.assign(n, rnd.next(8, 10));
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        t.push_back(rnd.next(1, 2));
        for (int i = 1; i < n; ++i) t.push_back(rnd.next(7, 10));
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        t.push_back(rnd.next(8, 10));
        for (int i = 1; i < n; ++i) t.push_back(rnd.next(1, 4));
    } else if (mode == 4) {
        n = rnd.next(3, 10);
        for (int i = 0; i < n; ++i) {
            t.push_back((i % 2 == 0) ? rnd.next(1, 3) : rnd.next(8, 10));
        }
    } else {
        n = rnd.next(1, 10);
        int lo = rnd.next(1, 7);
        int hi = rnd.next(lo, 10);
        for (int i = 0; i < n; ++i) t.push_back(rnd.next(lo, hi));
    }

    if (rnd.next(2) == 1 && t.size() > 1) {
        int first = t[0];
        vector<int> rest(t.begin() + 1, t.end());
        if (rnd.next(2) == 0) {
            sort(rest.begin(), rest.end());
        } else {
            sort(rest.rbegin(), rest.rend());
        }
        t.clear();
        t.push_back(first);
        t.insert(t.end(), rest.begin(), rest.end());
    }

    return t;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(8, 20);
    println(testCount);

    for (int tc = 0; tc < testCount; ++tc) {
        vector<int> t = makeCase(tc < 6 ? tc : rnd.next(0, 5));
        println((int)t.size());
        println(t);
    }

    return 0;
}
