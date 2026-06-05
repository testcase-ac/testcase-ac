#include "testlib.h"
#include <vector>
using namespace std;

int boundedValue(int lo, int hi) {
    return rnd.next(lo, hi);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int c;
    vector<int> values;

    if (mode == 0) {
        c = rnd.next(1, 8);
        values.resize(c);
        for (int i = 0; i < c; ++i) values[i] = -rnd.next(1, 1000);
    } else if (mode == 1) {
        c = rnd.next(2, 20);
        values.resize(c);
        int spike = rnd.next(0, c - 1);
        for (int i = 0; i < c; ++i) {
            if (i == spike) {
                values[i] = rnd.next(200, 1000);
            } else {
                values[i] = -rnd.next(0, 300);
            }
        }
    } else if (mode == 2) {
        c = rnd.next(3, 30);
        values.resize(c);
        for (int i = 0; i < c; ++i) {
            int magnitude = rnd.next(1, 1000);
            values[i] = (i % 2 == 0 ? magnitude : -magnitude);
        }
    } else if (mode == 3) {
        c = rnd.next(1, 100);
        values.resize(c);
        for (int i = 0; i < c; ++i) {
            int pick = rnd.next(0, 4);
            if (pick == 0) values[i] = -1000;
            else if (pick == 1) values[i] = 1000;
            else values[i] = rnd.next(-20, 20);
        }
    } else if (mode == 4) {
        c = rnd.next(1, 35);
        values.resize(c);
        for (int i = 0; i < c; ++i) {
            if (rnd.next(0, 4) == 0) {
                values[i] = boundedValue(-1000, 1000);
            } else {
                values[i] = boundedValue(-3, 3);
            }
        }
    } else {
        c = rnd.next(1, 100);
        values.resize(c);
        int lo = rnd.next(-1000, 200);
        int hi = rnd.next(max(lo, -200), 1000);
        for (int i = 0; i < c; ++i) values[i] = rnd.next(lo, hi);
    }

    println(c);
    for (int value : values) println(value);

    return 0;
}
