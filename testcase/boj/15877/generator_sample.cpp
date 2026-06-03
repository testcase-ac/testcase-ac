#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int clampCoord(int value) {
    return max(0, min(1000, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int a = 0;
    int b = 0;

    if (mode == 0) {
        a = rnd.next(0, 8);
        b = rnd.next(0, 8);
    } else if (mode == 1) {
        if (rnd.next(0, 1) == 0) {
            a = rnd.next(0, 1000);
            b = rnd.next(0, 12);
        } else {
            a = rnd.next(0, 12);
            b = rnd.next(0, 1000);
        }
    } else if (mode == 2) {
        int base = rnd.next(0, 250) * 4;
        a = clampCoord(base + rnd.next(-2, 3));
        b = clampCoord(base + rnd.next(-2, 3));
    } else if (mode == 3) {
        vector<pair<int, int>> moves = {{1, 0}, {0, 1}, {3, 1}, {1, 3}};
        pair<int, int> move = rnd.any(moves);
        int repeat = rnd.next(0, 250);
        a = clampCoord(move.first * repeat + rnd.next(0, 6));
        b = clampCoord(move.second * repeat + rnd.next(0, 6));
    } else if (mode == 4) {
        a = rnd.next(985, 1000);
        b = rnd.next(985, 1000);
    } else {
        a = rnd.next(0, 1000);
        b = rnd.next(0, 1000);
    }

    println(a, b);
    return 0;
}
