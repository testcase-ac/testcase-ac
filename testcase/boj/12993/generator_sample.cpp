#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

const int MAX_COORD = 1000000000;

long long pow3(int exp) {
    long long value = 1;
    while (exp--) value *= 3;
    return value;
}

pair<int, int> reachablePoint() {
    int maxDigit = rnd.next(0, 18);
    long long x = 0, y = 0;
    for (int i = 0; i <= maxDigit; ++i) {
        if (rnd.next(2) == 0)
            x += pow3(i);
        else
            y += pow3(i);
    }
    return {static_cast<int>(x), static_cast<int>(y)};
}

pair<int, int> ternaryNearMiss() {
    auto point = reachablePoint();
    int mode = rnd.next(4);

    if (mode == 0) {
        int digit = rnd.next(0, 18);
        point.first += static_cast<int>(pow3(digit));
    } else if (mode == 1) {
        int digit = rnd.next(0, 18);
        point.second += static_cast<int>(pow3(digit));
    } else if (mode == 2) {
        int digit = rnd.next(0, 18);
        int delta = static_cast<int>(pow3(digit));
        if (point.first >= delta) point.first -= delta;
        if (point.second >= delta) point.second -= delta;
    } else {
        point = {rnd.next(0, MAX_COORD), rnd.next(0, MAX_COORD)};
    }

    point.first = min(point.first, MAX_COORD);
    point.second = min(point.second, MAX_COORD);
    return point;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> edgeCases = {
        {0, 0},
        {0, MAX_COORD},
        {MAX_COORD, 0},
        {MAX_COORD, MAX_COORD},
        {1, 1},
        {3, 0},
        {1, 3},
        {3, 10},
    };

    pair<int, int> point;
    int mode = rnd.next(6);
    if (mode == 0) {
        point = rnd.any(edgeCases);
    } else if (mode <= 2) {
        point = reachablePoint();
    } else if (mode <= 4) {
        point = ternaryNearMiss();
    } else {
        point = {rnd.next(0, MAX_COORD), rnd.next(0, MAX_COORD)};
    }

    println(point.first, point.second);
    return 0;
}
