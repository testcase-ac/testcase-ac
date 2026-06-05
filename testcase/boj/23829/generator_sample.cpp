#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const int MIN_COORD = 1;
const int MAX_COORD = 10000000;

int clampCoord(int x) {
    return max(MIN_COORD, min(MAX_COORD, x));
}

int nearCoord(int center, int radius) {
    return clampCoord(center + rnd.next(-radius, radius));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    int q = rnd.next(1, 30);
    vector<int> p(n), x(q);

    if (mode == 0) {
        int value = rnd.next(MIN_COORD, MAX_COORD);
        for (int& v : p) v = value;
        for (int& v : x) v = rnd.any(vector<int>{MIN_COORD, value, MAX_COORD});
    } else if (mode == 1) {
        int center = rnd.next(20, MAX_COORD - 20);
        int radius = rnd.next(0, 20);
        for (int& v : p) v = nearCoord(center, radius);
        for (int& v : x) v = nearCoord(center, radius + rnd.next(0, 20));
    } else if (mode == 2) {
        for (int& v : p) v = rnd.any(vector<int>{MIN_COORD, MAX_COORD, rnd.next(MIN_COORD, MAX_COORD)});
        for (int& v : x) v = rnd.any(vector<int>{MIN_COORD, MAX_COORD, rnd.next(MIN_COORD, MAX_COORD)});
    } else if (mode == 3) {
        int start = rnd.next(MIN_COORD, MAX_COORD);
        int step = rnd.next(1, 1000);
        for (int i = 0; i < n; ++i) p[i] = clampCoord(start + i * step);
        for (int i = 0; i < q; ++i) x[i] = clampCoord(start + rnd.next(-5, n + 5) * step);
    } else if (mode == 4) {
        int hi = rnd.next(1, MAX_COORD);
        for (int& v : p) v = rnd.next(1, hi);
        for (int& v : x) v = rnd.next(1, hi);
    } else {
        for (int& v : p) v = rnd.next(MIN_COORD, MAX_COORD);
        for (int& v : x) v = rnd.next(MIN_COORD, MAX_COORD);
    }

    if (rnd.next(2)) shuffle(p.begin(), p.end());

    println(n, q);
    println(p);
    for (int v : x) println(v);

    return 0;
}
