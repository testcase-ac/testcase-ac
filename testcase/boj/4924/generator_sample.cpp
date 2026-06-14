#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

static pair<int, int> clippedRange(int center, int radius) {
    int low = max(1, center - radius);
    int high = min(999999, center + radius);
    return {low, high};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCases = rnd.next(6, 24);
    vector<pair<int, int>> ranges;
    ranges.reserve(testCases);

    while ((int)ranges.size() < testCases) {
        int mode = rnd.next(8);
        int l, u;

        if (mode == 0) {
            l = rnd.next(1, 25);
            u = rnd.next(l, min(60, l + rnd.next(0, 35)));
        } else if (mode == 1) {
            int x = rnd.next(1, 999999);
            l = x;
            u = x;
        } else if (mode == 2) {
            int base = rnd.any(vector<int>{1, 2, 4, 8, 16, 32, 64, 128, 256,
                                           512, 1024, 4096, 65536, 262144, 524288});
            int radius = rnd.next(0, 40);
            tie(l, u) = clippedRange(base, radius);
        } else if (mode == 3) {
            int base = rnd.any(vector<int>{6, 12, 18, 24, 36, 48, 60, 72, 120,
                                           180, 240, 360, 720, 840, 1260, 2520});
            int radius = rnd.next(0, 80);
            tie(l, u) = clippedRange(base, radius);
        } else if (mode == 4) {
            int base = rnd.any(vector<int>{99991, 100003, 199999, 524287, 524288,
                                           786432, 900000, 901000, 999983, 999999});
            int radius = rnd.next(0, 200);
            tie(l, u) = clippedRange(base, radius);
        } else if (mode == 5) {
            l = rnd.next(1, 999900);
            u = rnd.next(l, min(999999, l + rnd.next(1, 100)));
        } else if (mode == 6) {
            l = rnd.next(1, 998000);
            u = rnd.next(l + 100, min(999999, l + rnd.next(100, 2000)));
        } else {
            l = rnd.next(900000, 999999);
            u = rnd.next(l, 999999);
        }

        ranges.push_back({l, u});
    }

    shuffle(ranges.begin(), ranges.end());

    for (const auto& range : ranges) {
        println(range.first, range.second);
    }
    println(-1, -1);

    return 0;
}
