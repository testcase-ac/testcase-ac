#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    set<int> used;
    vector<int> positions;

    auto addPosition = [&](int value) {
        if (value != 0 && value >= -500000 && value <= 500000 && used.insert(value).second) {
            positions.push_back(value);
        }
    };

    auto addRandomFromRange = [&](int lo, int hi, int targetSize) {
        for (int attempts = 0; attempts < 200 && (int)positions.size() < targetSize; ++attempts) {
            int value = rnd.next(lo, hi);
            addPosition(value);
        }
    };

    if (mode == 0) {
        n = rnd.next(1, 18);
        addRandomFromRange(-80, -1, n);
    } else if (mode == 1) {
        n = rnd.next(1, 18);
        addRandomFromRange(1, 80, n);
    } else if (mode == 2) {
        n = rnd.next(2, 24);
        int leftCount = rnd.next(1, n - 1);
        addRandomFromRange(-40, -1, leftCount);
        addRandomFromRange(1, 40, n);
    } else if (mode == 3) {
        n = rnd.next(2, 20);
        int radius = rnd.next(1, 12);
        int leftCount = rnd.next(1, n - 1);
        addRandomFromRange(-radius, -1, leftCount);
        addRandomFromRange(1, radius, n);
    } else if (mode == 4) {
        n = rnd.next(4, 28);
        addPosition(-500000);
        addPosition(500000);
        int farLeftCount = rnd.next(2, n - 2);
        addRandomFromRange(-500000, -400000, farLeftCount);
        addRandomFromRange(400000, 500000, n - rnd.next(0, 3));
        addRandomFromRange(-100, 100, n);
    } else {
        n = rnd.next(8, 35);
        int leftLimit = rnd.next(10, 500);
        int rightLimit = rnd.next(10, 500);
        int leftCount = rnd.next(1, n - 1);
        addRandomFromRange(-leftLimit, -1, leftCount);
        addRandomFromRange(1, rightLimit, n);
    }

    while ((int)positions.size() < n) {
        int value = rnd.next(-500, 500);
        addPosition(value);
    }

    shuffle(positions.begin(), positions.end());

    println((int)positions.size());
    for (int p : positions) {
        println(p);
    }

    return 0;
}
