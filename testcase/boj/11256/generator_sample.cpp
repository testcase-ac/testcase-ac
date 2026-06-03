#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> makeBoxWithCapacity(int capacity) {
    int r = rnd.next(1, capacity);
    while (capacity % r != 0) {
        r = rnd.next(1, capacity);
    }
    return {r, capacity / r};
}

void ensureEnoughCapacity(vector<pair<int, int>>& boxes, int j) {
    long long total = 0;
    for (const auto& box : boxes) {
        total += 1LL * box.first * box.second;
    }

    if (total >= j) return;

    int missing = static_cast<int>(j - total);
    boxes.push_back(makeBoxWithCapacity(missing));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int j = rnd.next(1, 1000);
        vector<pair<int, int>> boxes;

        if (mode == 0) {
            int capacity = rnd.next(j, min(10000, j + 200));
            boxes.push_back(makeBoxWithCapacity(capacity));
        } else if (mode == 1) {
            int n = rnd.next(2, 12);
            int remaining = j;
            for (int i = 0; i < n; ++i) {
                int capacity = (i + 1 == n) ? remaining : rnd.next(1, max(1, remaining));
                boxes.push_back(makeBoxWithCapacity(capacity));
                remaining = max(1, remaining - capacity);
            }
        } else if (mode == 2) {
            int n = rnd.next(3, 15);
            int base = rnd.next(1, max(1, j / 2));
            for (int i = 0; i < n; ++i) {
                int capacity = max(1, base + rnd.next(-2, 2));
                boxes.push_back(makeBoxWithCapacity(capacity));
            }
        } else if (mode == 3) {
            int n = rnd.next(3, 18);
            for (int i = 0; i < n; ++i) {
                int side = rnd.next(1, 25);
                boxes.push_back({side, rnd.next(1, 40)});
            }
        } else {
            int n = rnd.next(2, 10);
            int capacity = rnd.next(1, 1000);
            for (int i = 0; i < n; ++i) {
                boxes.push_back(makeBoxWithCapacity(capacity));
            }
            j = rnd.next(1, min(1000, capacity * n));
        }

        ensureEnoughCapacity(boxes, j);
        shuffle(boxes.begin(), boxes.end());

        println(j, static_cast<int>(boxes.size()));
        for (const auto& box : boxes) {
            println(box.first, box.second);
        }
    }

    return 0;
}
