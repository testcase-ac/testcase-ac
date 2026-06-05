#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int nextValue(int lo, int hi) {
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = rnd.next(1, 18);
    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        int hi = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) a.push_back(nextValue(1, hi));
    } else if (mode == 1) {
        int lo = rnd.next(-30, -1);
        for (int i = 0; i < n; ++i) a.push_back(nextValue(lo, 0));
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) a.push_back(nextValue(-20, 20));
    } else if (mode == 3) {
        vector<int> pool = {-100000, -10000, -1, 0, 1, 10000, 100000};
        for (int i = 0; i < n; ++i) a.push_back(rnd.any(pool));
    } else if (mode == 4) {
        int positive = rnd.next(1, n);
        for (int i = 0; i < positive; ++i) a.push_back(nextValue(1, 25));
        for (int i = positive; i < n; ++i) a.push_back(nextValue(-25, 0));
    } else if (mode == 5) {
        int base = rnd.next(-8, 8);
        for (int i = 0; i < n; ++i) a.push_back(base + rnd.next(-2, 2));
    } else if (mode == 6) {
        for (int i = 0; i < n; ++i) {
            int v = rnd.next(-12, 12);
            a.push_back(v * v * (v < 0 ? -1 : 1));
        }
    } else {
        n = rnd.next(20, 60);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                a.push_back(0);
            } else {
                a.push_back(nextValue(-1000, 1000));
            }
        }
    }

    if (rnd.next(0, 2) == 0) shuffle(a.begin(), a.end());
    if (rnd.next(0, 5) == 0) sort(a.begin(), a.end());
    if (rnd.next(0, 5) == 0) reverse(a.begin(), a.end());

    println((int)a.size());
    println(a);

    return 0;
}
