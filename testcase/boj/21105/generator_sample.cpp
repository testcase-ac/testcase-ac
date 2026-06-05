#include "testlib.h"

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

string fixed2(int cents) {
    char buf[32];
    if (cents < 0) {
        cents = -cents;
        snprintf(buf, sizeof(buf), "-%d.%02d", cents / 100, cents % 100);
    } else {
        snprintf(buf, sizeof(buf), "%d.%02d", cents / 100, cents % 100);
    }
    return string(buf);
}

int randomCents(int lo, int hi) {
    return rnd.next(lo, hi);
}

int randomChange() {
    int mode = rnd.next(6);
    if (mode == 0) {
        vector<int> values = {-100000, -99999, -50000, -1, 0, 1, 10000, 100000};
        return rnd.any(values);
    }
    if (mode == 1) {
        return rnd.next(-99999, -99000);
    }
    if (mode == 2) {
        return rnd.next(-1000, 1000);
    }
    int c = rnd.next(-100000, 100000);
    if (c == -10000) {
        c += rnd.next(0, 1) ? 1 : -1;
    }
    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int mode = rnd.next(4);
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else {
        n = rnd.next(6, 12);
    }

    println(n);
    for (int i = 0; i < n; ++i) {
        int p;
        if (rnd.next(4) == 0) {
            vector<int> prices = {100, 101, 9999, 10000, 99999, 100000};
            p = rnd.any(prices);
        } else {
            p = randomCents(100, 100000);
        }

        int c = randomChange();
        println(fixed2(p), fixed2(c));
    }

    return 0;
}
