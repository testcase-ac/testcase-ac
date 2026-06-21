#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> makeInterval(int n, int mode) {
    if (mode == 0) {
        return {0, n};
    }
    if (mode == 1) {
        int x = rnd.next(0, n);
        return {x, x};
    }
    if (mode == 2) {
        int l = rnd.next(0, n);
        int width = rnd.next(0, min(n - l, 2));
        return {l, l + width};
    }
    if (mode == 3) {
        int r = rnd.next(0, n);
        int width = rnd.next(0, min(r, 2));
        return {r - width, r};
    }

    int l = rnd.next(0, n);
    int r = rnd.next(l, n);
    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(0, 9) == 0) {
        n = rnd.next(20, 60);
    } else {
        n = rnd.next(1, 12);
    }

    int q;
    if (rnd.next(0, 9) == 0) {
        q = rnd.next(20, 80);
    } else {
        q = rnd.next(1, 18);
    }

    int initialMode = rnd.next(0, 4);
    vector<pair<int, int>> intervals(n);
    for (int i = 0; i < n; ++i) {
        int mode = rnd.next(0, 99);
        if (initialMode == 0) {
            intervals[i] = makeInterval(n, mode < 60 ? 0 : rnd.next(1, 4));
        } else if (initialMode == 1) {
            intervals[i] = makeInterval(n, mode < 70 ? 1 : 4);
        } else if (initialMode == 2) {
            intervals[i] = makeInterval(n, mode < 80 ? 2 : 4);
        } else if (initialMode == 3) {
            intervals[i] = makeInterval(n, mode < 80 ? 3 : 4);
        } else {
            intervals[i] = makeInterval(n, 4);
        }
    }

    println(n);
    for (auto [l, r] : intervals) {
        println(l, r);
    }

    println(q);
    int hotPerson = rnd.next(1, n);
    for (int i = 0; i < q; ++i) {
        int p;
        if (i > 0 && rnd.next(0, 99) < 45) {
            p = hotPerson;
        } else {
            p = rnd.next(1, n);
        }

        int mode;
        int choice = rnd.next(0, 99);
        if (choice < 20) {
            mode = 0;
        } else if (choice < 45) {
            mode = 1;
        } else if (choice < 65) {
            mode = 2;
        } else if (choice < 85) {
            mode = 3;
        } else {
            mode = 4;
        }

        auto [l, r] = makeInterval(n, mode);
        println(p, l, r);
    }

    return 0;
}
