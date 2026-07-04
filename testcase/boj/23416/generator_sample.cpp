#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int clampValue(int x) {
    return max(2, min(100, x));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int a = 2;
    int b = 2;

    if (mode == 0) {
        a = rnd.next(2, 100);
        b = a;
    } else if (mode == 1) {
        a = rnd.next(2, 100);
        int delta = rnd.next(1, 6);
        b = clampValue(a + (rnd.next(0, 1) ? delta : -delta));
    } else if (mode == 2) {
        a = rnd.next(2, 12);
        b = rnd.next(2, 12);
    } else if (mode == 3) {
        a = rnd.next(90, 100);
        b = rnd.next(90, 100);
    } else if (mode == 4) {
        a = rnd.next(2, 12);
        b = rnd.next(80, 100);
    } else if (mode == 5) {
        int base = rnd.next(2, 20);
        a = base;
        b = base * rnd.next(2, 100 / base);
    } else {
        vector<pair<int, int>> edges = {
            {2, rnd.next(2, 100)},
            {rnd.next(2, 100), 2},
            {100, rnd.next(2, 100)},
            {rnd.next(2, 100), 100},
        };
        auto picked = rnd.any(edges);
        a = picked.first;
        b = picked.second;
    }

    if (rnd.next(0, 1)) swap(a, b);
    println(a, b);

    return 0;
}
