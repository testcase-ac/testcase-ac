#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int v0;
    int m;
    int t;

    if (mode == 0) {
        v0 = rnd.next(1, 10);
        m = rnd.next(1, 10);
        t = rnd.next(1, 12);
    } else if (mode == 1) {
        v0 = rnd.next(990, 1000);
        m = rnd.next(990, 1000);
        t = rnd.next(999999900, 1000000000);
    } else if (mode == 2) {
        v0 = rnd.next(1, 1000);
        m = rnd.any(vector<int>{10, 20, 50, 100, 250, 500, 1000});
        t = rnd.next(1, 1000000000);
    } else if (mode == 3) {
        v0 = rnd.any(vector<int>{1, 3, 7, 9, 11, 37, 99, 101, 999});
        m = rnd.any(vector<int>{1, 3, 7, 9, 11, 37, 99, 101, 999});
        t = rnd.next(1, 1000000000);
    } else if (mode == 4) {
        v0 = rnd.next(1, 1000);
        m = rnd.next(1, 1000);
        t = rnd.any(vector<int>{1, 2, 3, 4, 5, 8, 16, 32});
    } else if (mode == 5) {
        v0 = rnd.next(1, 1000);
        m = rnd.next(1, 1000);
        int base = rnd.any(vector<int>{1000, 10000, 1000000, 1000000000});
        t = max(1, base - rnd.next(0, min(base - 1, 100)));
    } else if (mode == 6) {
        int lastDigit = rnd.any(vector<int>{0, 2, 4, 5, 6, 8});
        v0 = rnd.next(0, 99) * 10 + lastDigit;
        if (v0 == 0) v0 = 10;
        m = rnd.next(1, 1000);
        t = rnd.next(1, 1000000000);
    } else {
        v0 = rnd.next(1, 1000);
        m = rnd.next(1, 1000);
        t = rnd.next(1, 1000000000);
    }

    println(v0, m, t);
    return 0;
}
