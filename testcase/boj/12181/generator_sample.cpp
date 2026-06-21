#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int T;
    if (mode == 0) {
        T = rnd.next(1, 8);
    } else if (mode == 1) {
        T = rnd.next(8, 20);
    } else if (mode == 2) {
        T = rnd.next(20, 40);
    } else {
        T = rnd.next(40, 100);
    }

    vector<pair<int, int>> cases;
    cases.reserve(T);

    auto addCase = [&](int r, int c) {
        cases.push_back({r, c});
    };

    vector<pair<int, int>> anchors = {
        {1, 1}, {1, 25}, {25, 1}, {25, 25},
        {2, 2}, {2, 25}, {25, 2}, {3, 3}
    };
    shuffle(anchors.begin(), anchors.end());

    int anchorCount = min<int>(T, rnd.next(0, min<int>(4, anchors.size())));
    for (int i = 0; i < anchorCount; ++i) {
        addCase(anchors[i].first, anchors[i].second);
    }

    while ((int)cases.size() < T) {
        int pattern = rnd.next(0, 5);
        int r, c;
        if (pattern == 0) {
            r = 1;
            c = rnd.next(1, 25);
        } else if (pattern == 1) {
            r = rnd.next(1, 25);
            c = 1;
        } else if (pattern == 2) {
            r = rnd.next(2, 8);
            c = rnd.next(2, 8);
        } else if (pattern == 3) {
            r = rnd.next(18, 25);
            c = rnd.next(18, 25);
        } else if (pattern == 4) {
            r = rnd.next(2, 25);
            c = r;
        } else {
            r = rnd.next(1, 25);
            c = rnd.next(1, 25);
        }
        addCase(r, c);
    }

    shuffle(cases.begin(), cases.end());

    println(T);
    for (auto [r, c] : cases) {
        println(r, c);
    }

    return 0;
}
