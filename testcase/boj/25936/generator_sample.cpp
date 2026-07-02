#include "testlib.h"
#include <algorithm>
#include <cmath>
#include <utility>
#include <vector>
using namespace std;

static pair<int, int> clampCase(int s, int r) {
    s = max(1, min(100, s));
    r = max(1, min(100, r));
    return {s, r};
}

static pair<int, int> makePartialCase() {
    for (int attempt = 0; attempt < 200; ++attempt) {
        int r = rnd.next(2, 100);
        int low = r + 1;
        int high = min(100, 2 * r);
        if (low > high) continue;
        int s = rnd.next(low, high);
        if (2 * r >= s && sqrt(2.0) * r <= s) return {s, r};
    }
    return {10, 4};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(8, 30);
    vector<pair<int, int>> cases;
    cases.reserve(n);

    vector<pair<int, int>> anchors = {
        {1, 1},
        {100, 100},
        {2, 1},
        {3, 1},
        {8, 5},
        {10, 4},
    };
    shuffle(anchors.begin(), anchors.end());
    int anchorCount = rnd.next(1, min<int>(4, anchors.size()));
    for (int i = 0; i < anchorCount && (int)cases.size() < n; ++i) {
        cases.push_back(anchors[i]);
    }

    while ((int)cases.size() < n) {
        int mode = rnd.next(0, 6);

        if (mode == 0) {
            int r = rnd.next(1, 49);
            cases.push_back(clampCase(2 * r + rnd.next(1, 4), r));
        } else if (mode == 1) {
            int r = rnd.next(1, 50);
            cases.push_back(clampCase(rnd.next(1, 2 * r), r));
        } else if (mode == 2) {
            cases.push_back(makePartialCase());
        } else if (mode == 3) {
            int r = rnd.next(1, 50);
            int delta = rnd.next(-2, 2);
            cases.push_back(clampCase(2 * r + delta, r));
        } else if (mode == 4) {
            int s = rnd.next(1, 100);
            int around = max(1, (int)ceil(s / sqrt(2.0)));
            cases.push_back(clampCase(s, around + rnd.next(-2, 2)));
        } else {
            cases.push_back({rnd.next(1, 100), rnd.next(1, 100)});
        }
    }

    println(n);
    for (auto [s, r] : cases) {
        println(s, r);
    }

    return 0;
}
