#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> randomInterval(int n) {
    int l = rnd.next(1, n - 1);
    int r = rnd.next(l, n - 1);
    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    int m;
    int a;
    int b;
    vector<pair<int, int>> intervals;

    if (mode == 0) {
        n = rnd.next(2, 25);
        m = rnd.next(1, min(8, n - 1));
        a = rnd.next(1, n);
        b = rnd.next(1, n);
        for (int i = 0; i < m; ++i) intervals.push_back(randomInterval(n));
    } else if (mode == 1) {
        n = rnd.next(6, 40);
        m = rnd.next(3, 12);
        a = rnd.next(1, n);
        b = rnd.next(1, n);
        int l = rnd.next(1, n - 1);
        int r = rnd.next(l, n - 1);
        for (int i = 0; i < m; ++i) {
            int dl = rnd.next(0, min(3, l - 1));
            int dr = rnd.next(0, min(3, n - 1 - r));
            intervals.push_back({l - dl, r + dr});
        }
    } else if (mode == 2) {
        n = rnd.next(8, 60);
        m = rnd.next(4, 15);
        a = rnd.next(1, n);
        b = rnd.next(1, n);
        int center = rnd.next(2, n - 1);
        for (int i = 0; i < m; ++i) {
            int radius = rnd.next(0, min(6, n - 2));
            int l = max(1, center - radius);
            int r = min(n - 1, center + rnd.next(0, radius));
            intervals.push_back({l, r});
        }
    } else if (mode == 3) {
        n = rnd.next(2, 35);
        m = rnd.next(1, min(10, n - 1));
        a = rnd.next(max(1, n - 5), n);
        b = rnd.next(1, min(n, 5));
        for (int i = 0; i < m; ++i) {
            if (rnd.next(2) == 0) {
                int r = rnd.next(1, n - 1);
                intervals.push_back({1, r});
            } else {
                int l = rnd.next(1, n - 1);
                intervals.push_back({l, n - 1});
            }
        }
    } else if (mode == 4) {
        n = rnd.next(30, 120);
        m = rnd.next(20, 60);
        a = rnd.next(1, n);
        b = rnd.next(1, n);
        for (int i = 0; i < m; ++i) {
            int l = rnd.next(1, n - 1);
            int width = rnd.next(0, min(10, n - 1 - l));
            intervals.push_back({l, l + width});
        }
    } else {
        n = rnd.next(90000, 100000);
        m = rnd.next(1, 100);
        a = rnd.next(max(1, n - 1000), n);
        b = rnd.next(1, min(n, 1000));
        for (int i = 0; i < m; ++i) intervals.push_back(randomInterval(n));
    }

    shuffle(intervals.begin(), intervals.end());

    println(n, m, a, b);
    for (auto [l, r] : intervals) println(l, r);

    return 0;
}
