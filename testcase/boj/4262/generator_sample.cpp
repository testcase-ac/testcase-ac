#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

namespace {

constexpr int kMaxH = 1000001;

int randomH(int lowIndex, int highIndex) {
    return 4 * rnd.next(lowIndex, highIndex) + 1;
}

void addH(set<int>& values, int h) {
    if (h < 1 || h > kMaxH) return;
    if (h % 4 == 1) values.insert(h);
}

void addNearbyH(set<int>& values, int center, int radiusSteps) {
    int centerIndex = (center - 1) / 4;
    int lo = max(0, centerIndex - radiusSteps);
    int hi = min((kMaxH - 1) / 4, centerIndex + radiusSteps);
    addH(values, randomH(lo, hi));
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    set<int> values;
    int mode = rnd.next(0, 5);
    int count = rnd.next(4, 18);

    if (mode == 0) {
        for (int i = 0; i < count; ++i) {
            addH(values, randomH(0, 30));
        }
    } else if (mode == 1) {
        vector<int> anchors = {1, 21, 25, 45, 65, 81, 85, 125, 789};
        for (int i = 0; i < count; ++i) {
            addNearbyH(values, rnd.any(anchors), rnd.next(0, 8));
        }
    } else if (mode == 2) {
        vector<int> anchors = {999901, 999941, 999981, 1000001};
        for (int i = 0; i < count; ++i) {
            addNearbyH(values, rnd.any(anchors), rnd.next(0, 40));
        }
    } else if (mode == 3) {
        int lo = rnd.next(0, 250000);
        int hi = rnd.next(lo, 250000);
        for (int i = 0; i < count; ++i) {
            addH(values, randomH(lo, hi));
        }
    } else {
        vector<int> anchors = {
            1, 5, 9, 13, 17, 21, 25, 45, 65, 81, 85, 125,
            625, 2025, 6561, 10001, 998001, 1000001
        };
        for (int i = 0; i < count; ++i) {
            addNearbyH(values, rnd.any(anchors), rnd.next(0, 20));
        }
    }

    vector<int> queries(values.begin(), values.end());
    shuffle(queries.begin(), queries.end());

    for (int h : queries) {
        println(h);
    }
    println(0);

    return 0;
}
