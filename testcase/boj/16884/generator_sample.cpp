#include "testlib.h"

#include <vector>

using namespace std;

int pickN() {
    int mode = rnd.next(0, 5);

    if (mode == 0) return rnd.next(1, 12);
    if (mode == 1) return rnd.next(1, 5000) * 2;
    if (mode == 2) return rnd.next(0, 4999) * 2 + 1;
    if (mode == 3) return rnd.any(vector<int>{1, 2, 3, 4, 9997, 9998, 9999, 10000});

    int base = rnd.next(1, 10000);
    if (mode == 4 && base < 10000) ++base;
    return base;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tMode = rnd.next(0, 3);
    int t;
    if (tMode == 0) {
        t = rnd.next(1, 8);
    } else if (tMode == 1) {
        t = rnd.next(9, 30);
    } else {
        t = rnd.next(31, 100);
    }

    println(t);
    for (int tc = 0; tc < t; ++tc) {
        println(pickN());
    }

    return 0;
}
