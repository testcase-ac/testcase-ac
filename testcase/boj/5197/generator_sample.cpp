#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int evenIn(int lo, int hi) {
    return 2 * rnd.next(lo / 2, hi / 2);
}

vector<int> buildCase(int mode) {
    int n;
    vector<int> v;

    if (mode == 0) {
        n = 1;
        v = {evenIn(0, 1000000000)};
    } else if (mode == 1) {
        n = 2;
        v = {evenIn(0, 40), evenIn(0, 80)};
    } else if (mode == 2) {
        n = rnd.next(1, 12);
        v.assign(n, 0);
    } else if (mode == 3) {
        n = rnd.next(3, 14);
        int x = evenIn(0, 80);
        v.assign(n, x);
    } else if (mode == 4) {
        n = rnd.next(3, 15);
        v.assign(n, 0);
        v[0] = evenIn(0, 30);
        for (int i = 1; i < n; ++i) {
            v[i] = (rnd.next(4) == 0) ? evenIn(200, 1000) : evenIn(0, 80);
        }
    } else if (mode == 5) {
        n = rnd.next(4, 18);
        v.assign(n, 0);
        v[0] = evenIn(20, 120);
        for (int i = 1; i < n; ++i) {
            v[i] = (i % 2 == 0) ? evenIn(0, 40) : evenIn(120, 300);
        }
        shuffle(v.begin() + 1, v.end());
    } else if (mode == 6) {
        n = rnd.next(3, 16);
        int base = evenIn(20, 200);
        v.assign(n, 0);
        v[0] = base + evenIn(0, 20);
        for (int i = 1; i < n; ++i) {
            int delta = evenIn(-20, 20);
            v[i] = max(0, base + delta);
            if (v[i] % 2 != 0) --v[i];
        }
    } else if (mode == 7) {
        n = rnd.next(2, 10);
        v.assign(n, 0);
        for (int i = 0; i < n; ++i) {
            int pick = rnd.next(5);
            if (pick == 0) v[i] = 0;
            else if (pick == 1) v[i] = 2;
            else if (pick == 2) v[i] = 999999998;
            else if (pick == 3) v[i] = 1000000000;
            else v[i] = evenIn(0, 1000);
        }
    } else {
        n = rnd.next(20, 100);
        v.assign(n, 0);
        int hi = rnd.next(20, 5000);
        if (hi % 2 != 0) ++hi;
        for (int i = 0; i < n; ++i) v[i] = evenIn(0, hi);
    }

    return v;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(3, 12);
    println(k);
    for (int tc = 0; tc < k; ++tc) {
        int mode = (tc < 9) ? tc : rnd.next(0, 8);
        vector<int> v = buildCase(mode);
        println(static_cast<int>(v.size()));
        for (int x : v) println(x);
    }

    return 0;
}
