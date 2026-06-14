#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int randomPrimeLike() {
    static const vector<int> values = {
        2, 3, 5, 7, 11, 97, 997, 1009, 10007, 99991, 999983
    };
    return rnd.any(values);
}

int randomDivisorRich() {
    static const vector<int> values = {
        1, 2, 4, 6, 12, 24, 36, 60, 120, 180, 240, 360,
        720, 840, 1260, 2520, 5040, 7560, 10080, 27720,
        55440, 83160, 166320, 332640, 498960, 720720, 1000000
    };
    return rnd.any(values);
}

int randomPower() {
    int base = rnd.next(2, 10);
    int value = 1;
    while (value <= 1000000 / base && rnd.next(0, 2) != 0) {
        value *= base;
    }
    return value;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(4, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, 18);
        if (tc == 0) n = 1;
        if (tc == 1) n = rnd.next(2, 5);

        vector<int> h(n);

        if (mode == 0) {
            int value = rnd.next(1, 4) == 1 ? 1000000 : randomDivisorRich();
            fill(h.begin(), h.end(), value);
        } else if (mode == 1) {
            for (int i = 0; i < n; ++i) h[i] = randomPrimeLike();
        } else if (mode == 2) {
            int base = rnd.next(2, 6);
            int value = 1;
            for (int i = 0; i < n; ++i) {
                if (value <= 1000000 / base && rnd.next(0, 2) != 0) value *= base;
                h[i] = value;
            }
        } else if (mode == 3) {
            for (int i = 0; i < n; ++i) {
                int a = rnd.next(1, 80);
                int b = rnd.next(1, 80);
                h[i] = min(1000000, a * b * rnd.next(1, 10));
            }
        } else if (mode == 4) {
            for (int i = 0; i < n; ++i) {
                h[i] = rnd.next(0, 3) == 0 ? 1000000 : randomPower();
            }
        } else {
            for (int i = 0; i < n; ++i) {
                h[i] = rnd.next(1, 1000000);
            }
        }

        if (rnd.next(0, 3) == 0) shuffle(h.begin(), h.end());

        println(n);
        println(h);
    }

    return 0;
}
