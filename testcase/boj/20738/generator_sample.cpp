#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 5);
    } else if (mode == 2) {
        n = rnd.next(3, 12);
    } else {
        n = rnd.next(6, 20);
    }

    vector<pair<int, int>> points;
    points.reserve(n);

    int baseOffset = rnd.next(-20, 20);
    int spread = rnd.next(0, 40);
    for (int i = 0; i < n; ++i) {
        int diff;
        if (mode == 0) {
            diff = rnd.next(-2000000, 2000000);
        } else if (mode == 1) {
            diff = baseOffset;
        } else if (mode == 2) {
            diff = baseOffset + rnd.next(-spread, spread);
        } else if (mode == 3) {
            diff = (i % 2 == 0 ? -spread : spread);
        } else if (mode == 4) {
            diff = rnd.next(-200, 200);
        } else {
            diff = rnd.next(-2000000, 2000000);
        }

        int lowX = max(-1000000, -1000000 - diff);
        int highX = min(1000000, 1000000 - diff);
        int x;
        if (mode == 5 && rnd.next(0, 3) == 0) {
            x = rnd.any(vector<int>{lowX, highX});
        } else {
            x = rnd.next(lowX, highX);
        }
        int y = x + diff;
        points.push_back({x, y});
    }

    shuffle(points.begin(), points.end());

    println(n);
    for (auto [x, y] : points) {
        println(x, y);
    }

    return 0;
}
