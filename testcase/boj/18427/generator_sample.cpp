#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, mode == 4 ? 18 : 8);
    int m = rnd.next(1, mode == 1 ? 10 : 6);
    int h = rnd.next(1, mode == 2 ? 1000 : 80);

    vector<vector<int>> blocks(n);
    for (int i = 0; i < n; ++i) {
        int count = rnd.next(1, m);
        vector<int> candidates;

        if (mode == 0) {
            int limit = rnd.next(max(1, h / 2), max(1, h + 8));
            for (int x = 1; x <= min(1000, limit); ++x) {
                candidates.push_back(x);
            }
        } else if (mode == 1) {
            int base = rnd.next(1, 20);
            for (int x = base; x <= min(1000, base + 90); x += rnd.next(1, 4)) {
                candidates.push_back(x);
            }
        } else if (mode == 2) {
            int low = rnd.next(700, 950);
            for (int x = low; x <= 1000; ++x) {
                candidates.push_back(x);
            }
        } else if (mode == 3) {
            int step = rnd.next(2, 9);
            for (int x = step; x <= min(1000, step * 80); x += step) {
                candidates.push_back(x);
            }
        } else {
            int limit = rnd.next(8, 35);
            for (int x = 1; x <= limit; ++x) {
                candidates.push_back(x);
            }
        }

        shuffle(candidates.begin(), candidates.end());
        count = min(count, static_cast<int>(candidates.size()));
        blocks[i].assign(candidates.begin(), candidates.begin() + count);
        sort(blocks[i].begin(), blocks[i].end());
    }

    if (mode == 0 && rnd.next(0, 1) == 0) {
        h = 0;
        for (const auto& row : blocks) {
            h += rnd.any(row);
            if (h > 1000) {
                h = rnd.next(1, 1000);
                break;
            }
        }
        h = max(1, h);
    }

    println(n, m, h);
    for (const auto& row : blocks) {
        println(row);
    }

    return 0;
}
