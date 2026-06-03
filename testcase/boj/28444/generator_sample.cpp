#include "testlib.h"
#include <algorithm>
#include <array>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    array<int, 5> v{};
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        for (int& x : v) x = rnd.next(0, 100);
    } else if (mode == 1) {
        for (int& x : v) x = rnd.next(0, 1) ? rnd.next(0, 5) : rnd.next(95, 100);
    } else if (mode == 2) {
        v = {0, rnd.next(0, 100), rnd.next(0, 100), rnd.next(0, 100), rnd.next(0, 100)};
        int zeroCount = rnd.next(1, 3);
        shuffle(v.begin(), v.end());
        for (int i = 0; i < zeroCount; ++i) v[i] = 0;
    } else if (mode == 3) {
        int base = rnd.next(1, 10);
        v = {base, rnd.next(1, 100), base, rnd.next(1, 10), rnd.next(1, 10)};
    } else if (mode == 4) {
        v = {100, 100, rnd.next(0, 100), rnd.next(0, 100), rnd.next(0, 100)};
        shuffle(v.begin(), v.end());
    } else {
        int lo = rnd.next(0, 80);
        int hi = rnd.next(lo, 100);
        for (int& x : v) x = rnd.next(lo, hi);
    }

    println(v[0], v[1], v[2], v[3], v[4]);
    return 0;
}
