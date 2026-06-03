#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_A = (1 << 30) - 1;
    int mode = rnd.next(0, 6);
    int n = 1;
    vector<int> a;

    if (mode == 0) {
        n = rnd.next(1, 8);
        vector<int> pool = {0, 1, 2, 3, MAX_A, 1 << rnd.next(0, 29)};
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.any(pool));
        }
    } else if (mode == 1) {
        n = rnd.next(1, 40);
        int value = rnd.next(0, 2) == 0 ? 0 : MAX_A;
        a.assign(n, value);
    } else if (mode == 2) {
        n = rnd.next(2, 50);
        int x = rnd.next(0, MAX_A);
        int y = rnd.next(0, MAX_A);
        for (int i = 0; i < n; ++i) {
            a.push_back(i % 2 == 0 ? x : y);
        }
    } else if (mode == 3) {
        n = rnd.next(2, 60);
        for (int i = 0; i < n; ++i) {
            int bit = rnd.next(0, 29);
            int value = 1 << bit;
            if (rnd.next(0, 3) == 0) {
                value |= 1 << rnd.next(0, 29);
            }
            a.push_back(value);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 70);
        int base = rnd.next(0, MAX_A);
        for (int i = 0; i < n; ++i) {
            int flips = rnd.next(0, 5);
            int value = base;
            for (int j = 0; j < flips; ++j) {
                value ^= 1 << rnd.next(0, 29);
            }
            a.push_back(value);
        }
    } else if (mode == 5) {
        n = rnd.next(2, 80);
        int highMask = ((1 << rnd.next(15, 30)) - 1);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, highMask));
        }
    } else {
        n = rnd.next(1, 80);
        for (int i = 0; i < n; ++i) {
            a.push_back(rnd.next(0, MAX_A));
        }
    }

    println(n);
    println(a);

    return 0;
}
