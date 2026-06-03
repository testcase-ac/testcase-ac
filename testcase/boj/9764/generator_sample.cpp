#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int triangular(int k) {
    return k * (k + 1) / 2;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t = (mode == 1 ? 20 : rnd.next(1, 20));
    vector<int> ns;

    if (mode == 0) {
        t = rnd.next(1, 10);
        for (int i = 0; i < t; ++i) {
            ns.push_back(rnd.next(1, 30));
        }
    } else if (mode == 1) {
        ns = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10,
              50, 100, 199, 200, 499, 500, 999, 1000, 1999, 2000};
        shuffle(ns.begin(), ns.end());
    } else if (mode == 2) {
        t = rnd.next(5, 20);
        for (int i = 0; i < t; ++i) {
            int k = rnd.next(1, 62);
            int base = triangular(k);
            int delta = rnd.next(-2, 2);
            ns.push_back(max(1, min(2000, base + delta)));
        }
    } else if (mode == 3) {
        int center = rnd.next(1, 2000);
        int radius = rnd.next(0, 25);
        for (int i = 0; i < t; ++i) {
            int value = center + rnd.next(-radius, radius);
            ns.push_back(max(1, min(2000, value)));
        }
    } else if (mode == 4) {
        for (int i = 0; i < t; ++i) {
            int band = rnd.next(0, 3);
            if (band == 0) ns.push_back(rnd.next(1, 20));
            else if (band == 1) ns.push_back(rnd.next(21, 300));
            else if (band == 2) ns.push_back(rnd.next(301, 1200));
            else ns.push_back(rnd.next(1201, 2000));
        }
    } else {
        t = rnd.next(10, 20);
        int repeated = rnd.next(1, 2000);
        for (int i = 0; i < t; ++i) {
            if (rnd.next(0, 3) == 0) ns.push_back(repeated);
            else ns.push_back(rnd.next(1, 2000));
        }
    }

    println((int)ns.size());
    for (int n : ns) {
        println(n);
    }

    return 0;
}
