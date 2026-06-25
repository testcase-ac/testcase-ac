#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(2, 4);
    } else {
        n = rnd.next(3, 25);
    }

    vector<int> e(n - 1, 0);

    if (mode == 0) {
        for (int& x : e) {
            x = rnd.next(0, 1);
        }
    } else if (mode == 1) {
        for (int& x : e) {
            x = 1;
        }
    } else if (mode == 2) {
        for (int& x : e) {
            x = 0;
        }
    } else if (mode == 3) {
        int good = rnd.next(0, n - 2);
        e[good] = 1;
    } else if (mode == 4) {
        int parity = rnd.next(0, 1);
        for (int i = 0; i < n - 1; ++i) {
            e[i] = (i % 2 == parity);
        }
    } else if (mode == 5) {
        int split = rnd.next(0, n - 1);
        for (int i = split; i < n - 1; ++i) {
            e[i] = 1;
        }
    } else {
        int blockCount = rnd.next(2, 5);
        int value = rnd.next(0, 1);
        int pos = 0;
        while (pos < n - 1) {
            int remaining = n - 1 - pos;
            int len = rnd.next(1, max(1, remaining / blockCount + 1));
            for (int i = 0; i < len && pos < n - 1; ++i, ++pos) {
                e[pos] = value;
            }
            value ^= 1;
        }
    }

    println(n);
    println(e);
    return 0;
}
