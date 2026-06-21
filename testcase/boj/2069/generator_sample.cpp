#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    vector<pair<int, int>> mountains;

    if (mode == 0) {
        int x = rnd.next(1, 15);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, 8);
            mountains.push_back({x, x + len});
            x += len + rnd.next(0, 3);
        }
    } else if (mode == 1) {
        int left = rnd.next(1, 25);
        int right = left + rnd.next(10, 35);
        mountains.push_back({left, right});
        for (int i = 1; i < n; ++i) {
            int innerLeft = rnd.next(left, right - 1);
            int innerRight = rnd.next(innerLeft + 1, right);
            mountains.push_back({innerLeft, innerRight});
        }
    } else if (mode == 2) {
        int base = rnd.next(1, 60);
        for (int i = 0; i < n; ++i) {
            int left = base + rnd.next(0, 10);
            int right = left + rnd.next(1, 18);
            mountains.push_back({left, right});
        }
    } else if (mode == 3) {
        int center = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            int span = rnd.next(1, 18);
            int shift = rnd.next(-6, 6);
            int left = max(1, center - span + shift);
            int right = min(32767, center + span + shift);
            if (left == right) ++right;
            mountains.push_back({left, right});
        }
    } else if (mode == 4) {
        int sharedLeft = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            int left = rnd.next(0, 1) == 0 ? sharedLeft : sharedLeft + rnd.next(0, 8);
            int right = left + rnd.next(1, 24);
            mountains.push_back({left, right});
        }
    } else {
        n = rnd.next(2, 10);
        for (int i = 0; i < n; ++i) {
            int left = rnd.next(1, 32766);
            int right = rnd.next(left + 1, 32767);
            mountains.push_back({left, right});
        }
    }

    shuffle(mountains.begin(), mountains.end());

    println(static_cast<int>(mountains.size()));
    for (auto [left, right] : mountains) {
        println(left, right);
    }

    return 0;
}
