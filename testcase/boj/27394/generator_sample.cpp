#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int t = 0;
    int s = 0;

    if (mode == 0) {
        s = rnd.next(0, 30);
        t = rnd.next(0, 30);
    } else if (mode == 1) {
        s = rnd.next(1, 80);
        t = rnd.next(0, max(0, s / 2));
    } else if (mode == 2) {
        s = rnd.next(1, 80);
        t = rnd.next(s, min(1000000, 2 * s + 20));
    } else if (mode == 3) {
        s = rnd.next(1, 80);
        t = max(0, s + rnd.next(-3, 3));
    } else if (mode == 4) {
        int base = rnd.next(999900, 1000000);
        s = base;
        t = rnd.next(max(0, base - 100), 1000000);
    } else if (mode == 5) {
        s = rnd.next(0, 1000000);
        t = rnd.any(vector<int>{0, 1, 2, 999999, 1000000});
    } else if (mode == 6) {
        t = rnd.next(0, 1000000);
        s = rnd.any(vector<int>{0, 1, 2, 999999, 1000000});
    } else {
        s = rnd.next(0, 1000000);
        int span = rnd.next(0, 10000);
        t = rnd.next(max(0, s - span), min(1000000, s + span));
    }

    println(t, s);
    return 0;
}
