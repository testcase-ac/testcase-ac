#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    vector<int> p;

    if (mode == 0) {
        n = rnd.next(1, 8);
        int value = rnd.next(1, 100);
        p.assign(n, value);
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        int lo = rnd.next(1, 40);
        int hi = rnd.next(60, 100);
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.next(0, 1) ? hi : lo;
        }
    } else if (mode == 2) {
        n = rnd.next(5, 35);
        int center = rnd.next(25, 85);
        int spread = rnd.next(0, 15);
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            p[i] = min(100, max(1, center + rnd.next(-spread, spread)));
        }
    } else if (mode == 3) {
        n = rnd.next(10, 60);
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 4) == 0) {
                p[i] = rnd.next(1, 100);
            } else {
                p[i] = rnd.next(70, 100);
            }
        }
    } else if (mode == 4) {
        n = rnd.next(10, 80);
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.next(1, 35);
        }
    } else {
        n = rnd.next(50, 100);
        vector<int> extremes = {1, 2, 5, 95, 99, 100};
        p.resize(n);
        for (int i = 0; i < n; ++i) {
            p[i] = rnd.next(0, 9) == 0 ? rnd.next(1, 100) : rnd.any(extremes);
        }
    }

    shuffle(p.begin(), p.end());

    println(n);
    println(p);
    return 0;
}
