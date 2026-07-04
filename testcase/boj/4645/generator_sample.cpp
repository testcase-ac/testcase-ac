#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, pair<int, int>>> ranges = {
        {1, {0, 2}},
        {2, {0, 4}},
        {3, {1, 7}},
        {4, {0, 16}},
        {5, {rnd.next(0, 15), rnd.next(16, 32)}},
        {rnd.next(6, 10), {0, 0}},
        {rnd.next(11, 20), {0, 0}},
        {30, {1, (1 << 30) - 1}},
    };

    int extra = rnd.next(4, 10);
    for (int i = 0; i < extra; ++i) {
        int n = rnd.next(1, 30);
        int limit = 1 << n;
        int x1 = rnd.next(0, limit - 1);
        int x2 = rnd.next(x1 + 1, limit);
        ranges.push_back({n, {x1, x2}});
    }

    shuffle(ranges.begin(), ranges.end());

    int datasets = rnd.next(8, min<int>(18, ranges.size()));
    for (int i = 0; i < datasets; ++i) {
        int n = ranges[i].first;
        int limit = 1 << n;
        int x1 = ranges[i].second.first;
        int x2 = ranges[i].second.second;

        if (x1 == 0 && x2 == 0) {
            int mode = rnd.next(0, 3);
            if (mode == 0) {
                x1 = 0;
                x2 = limit;
            } else if (mode == 1) {
                x1 = rnd.next(0, limit / 2);
                x2 = rnd.next(limit / 2 + 1, limit);
            } else {
                x1 = rnd.next(0, limit - 1);
                x2 = rnd.next(x1 + 1, min(limit, x1 + rnd.next(1, 64)));
            }
        }

        int yMode = rnd.next(0, 5);
        int y;
        if (yMode == 0) {
            y = 0;
        } else if (yMode == 1) {
            y = limit;
        } else if (yMode == 2) {
            y = limit / 2;
        } else {
            y = rnd.next(0, limit);
        }

        println(n, x1, x2, y);
    }

    println(0);
    return 0;
}
