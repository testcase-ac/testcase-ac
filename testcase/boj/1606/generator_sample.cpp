#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MAX_COORD = 1000000;
    int mode = rnd.next(0, 6);
    int x = 0;
    int y = 0;

    if (mode == 0) {
        int limit = rnd.next(0, 12);
        x = rnd.next(0, limit);
        y = rnd.next(0, limit);
    } else if (mode == 1) {
        int value = rnd.next(0, 80);
        if (rnd.next(0, 1) == 0) {
            x = value;
            y = 0;
        } else {
            x = 0;
            y = value;
        }
    } else if (mode == 2) {
        int base = rnd.next(0, 120);
        int delta = rnd.next(0, 12);
        x = base;
        y = min(MAX_COORD, base + delta);
    } else if (mode == 3) {
        int sum = rnd.next(0, 200);
        x = rnd.next(0, sum);
        y = sum - x;
    } else if (mode == 4) {
        int near = rnd.next(0, 1000);
        x = MAX_COORD - near;
        y = rnd.next(0, 1000);
    } else if (mode == 5) {
        int near = rnd.next(0, 1000);
        x = rnd.next(0, 1000);
        y = MAX_COORD - near;
    } else {
        vector<pair<int, int>> anchors = {
            {0, 0},
            {0, 1},
            {1, 0},
            {1, 1},
            {0, MAX_COORD},
            {MAX_COORD, 0},
            {MAX_COORD, MAX_COORD},
        };
        tie(x, y) = rnd.any(anchors);
    }

    println(x, y);
    return 0;
}
