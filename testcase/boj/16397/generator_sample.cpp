#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int buttonB(int n) {
    int doubled = n * 2;
    if (doubled >= 100000) return -1;
    if (doubled == 0) return 0;

    int place = 1;
    while (place * 10 <= doubled) place *= 10;
    return doubled - place;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;
    int t = 1;
    int g = 0;

    if (mode == 0) {
        n = rnd.any(vector<int>{0, 1, 9, 10, 9999, 50000, 99999, rnd.next(0, 99999)});
        g = n;
        t = rnd.next(1, 99999);
    } else if (mode == 1) {
        n = rnd.next(0, 99950);
        int distance = rnd.next(0, min(80, 99999 - n));
        g = n + distance;
        t = rnd.next(max(1, distance), min(99999, max(1, distance) + rnd.next(0, 30)));
    } else if (mode == 2) {
        n = rnd.next(0, 49999);
        g = buttonB(n);
        if (g < 0) g = rnd.next(0, 99999);
        t = rnd.next(1, 20);
    } else if (mode == 3) {
        n = rnd.next(49990, 99999);
        g = rnd.any(vector<int>{0, 1, 99998, 99999, rnd.next(0, 99999)});
        t = rnd.any(vector<int>{1, 2, 10, 99999, rnd.next(1, 200)});
    } else if (mode == 4) {
        n = rnd.next(0, 120);
        g = rnd.next(0, 250);
        t = rnd.next(1, 25);
    } else {
        n = rnd.next(0, 99999);
        g = rnd.next(0, 99999);
        t = rnd.next(1, 99999);
    }

    println(n, t, g);
    return 0;
}
