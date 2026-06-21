#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_N = 10000000;
    int mode = rnd.next(0, 5);
    int a = 1;
    int b = 1;

    if (mode == 0) {
        a = b = rnd.next(1, 80);
    } else if (mode == 1) {
        a = rnd.next(1, 50);
        b = min(MAX_N, a + rnd.next(0, 35));
    } else if (mode == 2) {
        vector<int> anchors = {1, 2, 3, 6, 12, 24, 28, 48, 496, 8128};
        int center = rnd.any(anchors);
        int radius = rnd.next(0, 12);
        a = max(1, center - rnd.next(0, radius));
        b = min(MAX_N, center + rnd.next(0, radius));
    } else if (mode == 3) {
        int width = rnd.next(0, 20);
        b = MAX_N - rnd.next(0, 200);
        a = max(1, b - width);
    } else if (mode == 4) {
        int base = rnd.next(1, 100000);
        int width = rnd.next(0, 40);
        a = base;
        b = min(MAX_N, base + width);
    } else {
        vector<pair<int, int>> ranges = {
            {1, 9},
            {24, 24},
            {9999900, 10000000},
            {8120, 8135},
            {490, 505},
        };
        auto range = rnd.any(ranges);
        a = range.first;
        b = range.second;
    }

    println(a, b);
    return 0;
}
