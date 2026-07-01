#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    vector<int> c;

    if (mode == 0) {
        n = rnd.next(1, 8);
        c.assign(n, rnd.next(0, 3));
    } else if (mode == 1) {
        n = rnd.next(2, 25);
        c.resize(n);
        for (int i = 0; i < n; ++i) c[i] = rnd.next(0, 3);
    } else if (mode == 2) {
        n = rnd.next(3, 30);
        c.assign(n, 0);
        int active = rnd.next(1, n);
        vector<int> pos(n);
        for (int i = 0; i < n; ++i) pos[i] = i;
        shuffle(pos.begin(), pos.end());
        for (int i = 0; i < active; ++i) c[pos[i]] = rnd.next(1, 3);
    } else if (mode == 3) {
        n = rnd.next(4, 30);
        c.resize(n);
        int a = rnd.next(0, 3);
        int b = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) c[i] = (i % 2 == 0 ? a : b);
    } else if (mode == 4) {
        n = rnd.next(5, 35);
        c.resize(n);
        int left = rnd.next(0, 3);
        int middle = rnd.next(0, 3);
        int right = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) {
            if (i < n / 3) c[i] = left;
            else if (i < 2 * n / 3) c[i] = middle;
            else c[i] = right;
        }
    } else if (mode == 5) {
        n = rnd.next(10, 45);
        c.resize(n);
        for (int i = 0; i < n; ++i) {
            int phase = i % 4;
            c[i] = (phase == 0 ? 0 : phase);
        }
        int edits = rnd.next(1, n / 2);
        for (int i = 0; i < edits; ++i) c[rnd.next(0, n - 1)] = rnd.next(0, 3);
    } else {
        n = rnd.next(30, 80);
        c.resize(n);
        int lo = rnd.next(0, 2);
        int hi = rnd.next(lo, 3);
        for (int i = 0; i < n; ++i) c[i] = rnd.next(lo, hi);
    }

    println(n);
    println(c);
    return 0;
}
