#include "testlib.h"
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> cases;
    vector<pair<int, int>> anchors = {
        {0, 0},
        {0, 59},
        {1, 1},
        {2, 29},
        {2, 30},
        {4, 30},
        {4, 31},
        {8, 14},
        {12, 31},
        {13, 1},
        {23, 59},
        {24, 0},
        {99, 99}
    };

    shuffle(anchors.begin(), anchors.end());

    int mode = rnd.next(5);
    int target = rnd.next(8, 25);

    if (mode == 0) {
        target = rnd.next(1, 8);
    } else if (mode == 1) {
        target = rnd.next(20, 40);
    }

    int maxAnchorCount = min<int>(target, anchors.size());
    int minAnchorCount = min(3, maxAnchorCount);
    int anchorCount = rnd.next(minAnchorCount, maxAnchorCount);
    for (int i = 0; i < anchorCount; ++i) {
        cases.push_back(anchors[i]);
    }

    while ((int)cases.size() < target) {
        int x, y;
        int kind = rnd.next(6);

        if (kind == 0) {
            x = rnd.next(0, 23);
            y = rnd.next(0, 59);
        } else if (kind == 1) {
            x = rnd.next(1, 12);
            vector<int> monthDays = {0, 1, 28, 29, 30, 31, 32};
            y = rnd.any(monthDays);
        } else if (kind == 2) {
            x = rnd.next(13, 23);
            y = rnd.next(1, 59);
        } else if (kind == 3) {
            x = rnd.next(24, 99);
            y = rnd.next(0, 99);
        } else if (kind == 4) {
            x = rnd.next(0, 99);
            y = rnd.next(60, 99);
        } else {
            x = rnd.next(0, 99);
            y = rnd.next(0, 99);
        }

        cases.push_back({x, y});
    }

    shuffle(cases.begin(), cases.end());

    println((int)cases.size());
    for (auto [x, y] : cases) {
        println(x, y);
    }

    return 0;
}
