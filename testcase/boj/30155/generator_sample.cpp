#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int t = mode == 0 ? rnd.next(1, 3) : rnd.next(4, 20);
    println(t);

    vector<int> importantValues = {
        -1000000000, -999999999, -100000000, -1, 0, 1,
        2, 100000000, 999999999, 1000000000
    };
    vector<int> importantN = {
        1, 2, 3, 4, 5, 6, 7, 12, 999999995, 999999996,
        999999997, 999999998, 999999999, 1000000000
    };

    for (int tc = 0; tc < t; ++tc) {
        int a;
        int b;
        int n;

        if (mode == 0) {
            a = rnd.any(importantValues);
            b = rnd.any(importantValues);
            n = rnd.next(1, 6);
        } else if (mode == 1) {
            a = rnd.next(-10, 10);
            b = rnd.next(-10, 10);
            n = rnd.any(importantN);
        } else if (mode == 2) {
            a = rnd.next(-1000000000, 1000000000);
            b = rnd.next(-1000000000, 1000000000);
            n = rnd.next(1, 1000000000);
        } else if (mode == 3) {
            a = rnd.any(importantValues);
            b = rnd.next(-1000, 1000);
            n = 6 * rnd.next(0, 166666666) + rnd.next(1, 6);
            if (n > 1000000000) n -= 6;
        } else if (mode == 4) {
            a = rnd.next(-1000, 1000);
            b = rnd.any(importantValues);
            n = rnd.any(importantN);
        } else {
            a = rnd.next(-1000000, 1000000);
            b = a + rnd.next(-20, 20);
            n = rnd.next(1, 60);
        }

        println(a, b, n);
    }

    return 0;
}
