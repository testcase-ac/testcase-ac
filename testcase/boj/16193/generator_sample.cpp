#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(3, 20);
    if (mode == 5) n = rnd.next(21, 80);

    vector<int> a;
    a.reserve(n);

    if (mode == 0) {
        int value = rnd.next(-100000, 100000);
        a.assign(n, value);
    } else if (mode == 1) {
        int lo = rnd.next(-100000, -1);
        int hi = rnd.next(0, 100000);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, 1) == 0 ? lo : hi);
        }
    } else if (mode == 2) {
        int center = rnd.next(-90000, 90000);
        int spread = rnd.next(0, 10000);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(center - spread, center + spread));
        }
    } else if (mode == 3) {
        int lo = rnd.next(-100000, 0);
        int hi = rnd.next(0, 100000);
        int mid = rnd.next(lo, hi);
        for (int i = 0; i < n; ++i) {
            int bucket = rnd.next(0, 2);
            if (bucket == 0) a.push_back(lo);
            else if (bucket == 1) a.push_back(mid);
            else a.push_back(hi);
        }
    } else if (mode == 4) {
        int step = rnd.next(1, min(20000, 200000 / (n - 1)));
        int start = rnd.next(-100000, 100000 - step * (n - 1));
        for (int i = 0; i < n; ++i) {
            a.push_back(start + step * i);
        }
    } else {
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(-100000, 100000));
        }
    }

    shuffle(a.begin(), a.end());

    println(n);
    println(a);
    return 0;
}
