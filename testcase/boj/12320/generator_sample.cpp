#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

int nonZeroCoord() {
    int value = rnd.next(-1000000, 1000000);
    while (value == 0) {
        value = rnd.next(-1000000, 1000000);
    }
    return value;
}

int smallCoord() {
    return rnd.next(-5, 5);
}

int smallNonZeroCoord() {
    int value = smallCoord();
    while (value == 0) {
        value = smallCoord();
    }
    return value;
}

pair<int, int> randomTarget() {
    int mode = rnd.next(8);

    if (mode == 0) {
        return {smallCoord(), smallNonZeroCoord()};
    }
    if (mode == 1) {
        return {smallNonZeroCoord(), smallCoord()};
    }
    if (mode == 2) {
        int axis = rnd.next(2);
        int value = rnd.next(1, 1000000);
        if (rnd.next(2)) {
            value = -value;
        }
        return axis == 0 ? make_pair(value, 0) : make_pair(0, value);
    }
    if (mode == 3) {
        vector<int> edgeValues = {-1000000, -999999, -1, 1, 999999, 1000000};
        return {rnd.any(edgeValues), rnd.any(edgeValues)};
    }
    if (mode == 4) {
        int signX = rnd.next(2) ? 1 : -1;
        int signY = rnd.next(2) ? 1 : -1;
        return {signX * rnd.next(1, 1000), signY * rnd.next(1, 1000)};
    }
    if (mode == 5) {
        int x = rnd.next(-50, 50);
        int y = rnd.next(-50, 50);
        if (x == 0 && y == 0) {
            x = rnd.next(2) ? 1 : -1;
        }
        return {x, y};
    }
    if (mode == 6) {
        int x = rnd.next(900000, 1000000);
        int y = rnd.next(-1000000, -900000);
        if (rnd.next(2)) {
            swap(x, y);
        }
        return {x, y};
    }

    int x = rnd.next(-1000000, 1000000);
    int y = rnd.next(-1000000, 1000000);
    if (x == 0 && y == 0) {
        y = rnd.next(2) ? 1 : -1;
    }
    return {x, y};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 100);
    vector<pair<int, int>> targets;
    targets.reserve(t);

    for (int i = 0; i < t; ++i) {
        targets.push_back(randomTarget());
    }

    println(t);
    for (const auto& target : targets) {
        println(target.first, target.second);
    }

    return 0;
}
