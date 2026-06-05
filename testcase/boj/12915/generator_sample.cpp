#include "testlib.h"
#include <array>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int LIMIT = 100000;
    array<int, 5> a{};
    int mode = rnd.next(0, 6);

    if (mode == 0) {
        int hi = rnd.next(0, 20);
        for (int& x : a) x = rnd.next(0, hi);
    } else if (mode == 1) {
        int target = rnd.next(1, 200);
        a = {target + rnd.next(0, 3), rnd.next(0, target), target + rnd.next(0, 3),
             rnd.next(0, target), target + rnd.next(0, 3)};
    } else if (mode == 2) {
        int target = rnd.next(1, 500);
        a = {rnd.next(0, target / 2), target + rnd.next(0, target),
             rnd.next(0, target / 2), target + rnd.next(0, target),
             target + rnd.next(0, target)};
    } else if (mode == 3) {
        int target = rnd.next(1, 500);
        a = {target + rnd.next(0, target), target + rnd.next(0, target),
             rnd.next(0, target / 2), target + rnd.next(0, target),
             rnd.next(0, target / 2)};
    } else if (mode == 4) {
        int base = rnd.next(0, LIMIT - 500);
        for (int& x : a) x = base + rnd.next(0, 500);
    } else if (mode == 5) {
        int big = rnd.next(LIMIT - 1000, LIMIT);
        int small = rnd.next(0, 10);
        a = {rnd.next(0, big), small, rnd.next(0, big), small, rnd.next(0, big)};
        shuffle(a.begin(), a.end());
    } else {
        for (int& x : a) x = rnd.next(0, LIMIT);
    }

    println(a[0], a[1], a[2], a[3], a[4]);
    return 0;
}
