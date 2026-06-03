#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int a = 1;
    int b = 1;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        a = rnd.next(1, 10000);
        b = a;
    } else if (mode == 1) {
        int base = rnd.next(1, 5000);
        a = base;
        b = base * rnd.next(1, 10000 / base);
    } else if (mode == 2) {
        int g = rnd.next(1, 100);
        int x = rnd.next(1, 10000 / g);
        int y = rnd.next(1, 10000 / g);
        a = g * x;
        b = g * y;
    } else if (mode == 3) {
        a = rnd.next(1, 100);
        b = rnd.next(9900, 10000);
    } else if (mode == 4) {
        vector<int> lows = {1, 2, 3, 5, 7, 11, 13, 97, 9973};
        vector<int> highs = {9991, 9992, 9999, 10000};
        a = rnd.any(lows);
        b = rnd.any(highs);
    } else {
        a = rnd.next(1, 10000);
        b = rnd.next(1, 10000);
    }

    if (rnd.next(0, 1)) {
        swap(a, b);
    }

    println(a, b);
    return 0;
}
