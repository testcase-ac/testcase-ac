#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(3, 30);
    int m = rnd.next(1, min(80, n * (n + 1) / 2));
    vector<pair<int, int>> ranges;

    if (mode == 0) {
        for (int i = 0; i < m; ++i) {
            int x = rnd.next(1, n);
            ranges.emplace_back(x, x);
        }
    } else if (mode == 1) {
        int maxLen = rnd.next(1, min(n, 6));
        for (int i = 0; i < m; ++i) {
            int len = rnd.next(1, maxLen);
            int l = rnd.next(1, n - len + 1);
            ranges.emplace_back(l, l + len - 1);
        }
    } else if (mode == 2) {
        int centerL = rnd.next(1, n - 1);
        int centerR = rnd.next(centerL + 1, n);
        for (int i = 0; i < m; ++i) {
            int l = rnd.next(1, centerL);
            int r = rnd.next(centerR, n);
            ranges.emplace_back(l, r);
        }
    } else if (mode == 3) {
        for (int i = 0; i < m; ++i) {
            if (rnd.next(0, 1) == 0) {
                int r = rnd.next(1, n);
                ranges.emplace_back(1, r);
            } else {
                int l = rnd.next(1, n);
                ranges.emplace_back(l, n);
            }
        }
    } else {
        for (int i = 0; i < m; ++i) {
            int l = rnd.next(1, n);
            int r = rnd.next(l, n);
            ranges.emplace_back(l, r);
        }
    }

    shuffle(ranges.begin(), ranges.end());

    println(n, m);
    for (auto range : ranges) {
        println(range.first, range.second);
    }

    return 0;
}
