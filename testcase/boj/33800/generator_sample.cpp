#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int clampTarget(long long value) {
    return static_cast<int>(min(1000000000LL, max(1LL, value)));
}

int nearSquareTarget() {
    int k = rnd.next(1, 22361);
    long long base = 1LL * k * k;
    if (rnd.next(2) == 1) {
        base *= 2;
    }
    return clampTarget(base + rnd.next(-5, 5));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(20, 80);
    vector<int> targets;
    targets.reserve(t);

    vector<int> anchors = {1, 2, 3, 4, 5, 10, 12, 20, 999999999, 1000000000};
    shuffle(anchors.begin(), anchors.end());
    for (int value : anchors) {
        if (static_cast<int>(targets.size()) < t) {
            targets.push_back(value);
        }
    }

    while (static_cast<int>(targets.size()) < t) {
        int mode = rnd.next(0, 4);
        if (mode == 0) {
            targets.push_back(rnd.next(1, 100));
        } else if (mode == 1) {
            targets.push_back(nearSquareTarget());
        } else if (mode == 2) {
            targets.push_back(rnd.next(1, 1000000));
        } else if (mode == 3) {
            targets.push_back(rnd.next(1000000000 - 100000, 1000000000));
        } else {
            targets.push_back(rnd.next(1, 1000000000));
        }
    }

    shuffle(targets.begin(), targets.end());

    println(t);
    for (int target : targets) {
        println(target);
    }

    return 0;
}
