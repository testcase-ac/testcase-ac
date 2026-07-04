#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> r;

    if (mode == 0) {
        n = rnd.next(1, 8);
        r.resize(n);
        for (int i = 0; i < n; ++i) r[i] = rnd.next(1, 10);
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        int value = rnd.any(vector<int>{1, 2, 999, 1000, rnd.next(1, 1000)});
        r.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 25);
        r.resize(n);
        for (int i = 0; i < n; ++i) r[i] = (i % 2 == 0 ? 1 : 1000);
    } else if (mode == 3) {
        n = rnd.next(5, 30);
        r.resize(n);
        int start = rnd.next(1, 1000);
        int step = rnd.next(1, 97);
        for (int i = 0; i < n; ++i) r[i] = 1 + (start + i * step - 1) % 1000;
    } else if (mode == 4) {
        n = rnd.next(10, 60);
        r.resize(n);
        int lo = rnd.next(1, 900);
        int hi = rnd.next(lo, 1000);
        for (int i = 0; i < n; ++i) r[i] = rnd.next(lo, hi);
    } else {
        n = rnd.next(200, 1000);
        r.resize(n);
        for (int i = 0; i < n; ++i) {
            r[i] = (rnd.next(0, 3) == 0 ? rnd.next(990, 1000) : rnd.next(1, 1000));
        }
    }

    println(n);
    println(r);
    return 0;
}
