#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 25);
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        m = 2 * n - 1;
    } else if (mode == 2) {
        n = rnd.next(2, 10);
        m = rnd.next(2 * n - 1, 2 * n + 8);
    } else if (mode == 3) {
        n = rnd.next(8, 20);
        m = rnd.next(2 * n - 1, 60);
    } else {
        n = rnd.next(1, 26);
        m = rnd.next(2 * n - 1, 100);
    }

    vector<pair<int, int>> all;
    for (int l = 1; l <= m; ++l) {
        for (int r = l; r <= m; ++r) {
            int width = r - l + 1;
            if (width >= 2 * n - 1 && width % 2 == 1) {
                all.emplace_back(l, r);
            }
        }
    }

    shuffle(all.begin(), all.end());

    int q;
    if (mode == 1) {
        q = 1;
    } else {
        q = rnd.next(1, min<int>(all.size(), rnd.next(1, 40)));
    }

    vector<pair<int, int>> intervals(all.begin(), all.begin() + q);

    if (rnd.next(0, 1)) {
        sort(intervals.begin(), intervals.end());
    } else if (rnd.next(0, 1)) {
        sort(intervals.begin(), intervals.end(), [](const auto& a, const auto& b) {
            int aw = a.second - a.first;
            int bw = b.second - b.first;
            if (aw != bw) return aw < bw;
            return a < b;
        });
    }

    println(n, m, q);
    for (auto [l, r] : intervals) {
        println(l, r);
    }

    return 0;
}
