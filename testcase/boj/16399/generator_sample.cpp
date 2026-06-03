#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int c = rnd.next(1, 30);
    int e = rnd.next(1, 8);
    int range = c / e;
    int n = 0;
    int d = 0;
    vector<int> s;
    vector<int> p;

    if (mode == 0) {
        d = rnd.next(1, 80);
    } else {
        n = rnd.next(1, mode == 1 ? 4 : 12);

        for (int i = 0; i < n; ++i) {
            int gap;
            if (mode == 2 && i == rnd.next(0, n - 1)) {
                gap = max(1, range + rnd.next(1, 8));
            } else if (range > 0 && mode != 3) {
                gap = rnd.next(1, min(15, max(1, range)));
            } else {
                gap = rnd.next(1, 15);
            }
            s.push_back(gap);
        }

        int stationDistance = 0;
        for (int gap : s) stationDistance += gap;

        int tail;
        if (mode == 4) {
            tail = rnd.next(1, 25);
        } else if (range > 0) {
            tail = rnd.next(0, min(15, max(0, range)));
        } else {
            tail = rnd.next(0, 15);
        }
        d = stationDistance + tail;

        if (mode == 3 && d > 60) {
            d = stationDistance;
        }
    }

    if (d > 10000) d = 10000;

    p.resize(n);
    if (mode == 1) {
        int price = rnd.next(1, 30);
        for (int i = 0; i < n; ++i) {
            price += rnd.next(-5, 5);
            price = max(1, min(100, price));
            p[i] = price;
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) p[i] = (i % 2 == 0 ? rnd.next(1, 10) : rnd.next(40, 100));
    } else {
        for (int i = 0; i < n; ++i) p[i] = rnd.next(1, 100);
    }

    println(c, e, d);
    println(n);
    if (n > 0) {
        println(s);
        println(p);
    }

    return 0;
}
