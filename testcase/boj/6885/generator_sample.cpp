#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

pair<int, int> randomInterval(int n) {
    int l = rnd.next(1, n);
    int r = rnd.next(l, n);
    return {l, r};
}

pair<int, int> centeredInterval(int n, int center, int radius) {
    int l = max(1, center - radius);
    int r = min(n, center + radius);
    return {l, r};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 3);
    } else if (mode == 1) {
        n = rnd.next(4, 9);
    } else {
        n = rnd.next(6, 30);
    }

    vector<pair<int, int>> rows;
    rows.reserve(n);

    if (mode == 0) {
        for (int i = 0; i < n; ++i) {
            rows.push_back(randomInterval(n));
        }
    } else if (mode == 1) {
        for (int i = 0; i < n; ++i) {
            int l = (i % 2 == 0 ? 1 : rnd.next(1, n));
            int r = (i % 2 == 0 ? rnd.next(l, n) : n);
            rows.push_back({l, r});
        }
    } else if (mode == 2) {
        for (int i = 0; i < n; ++i) {
            int col = (i % 3 == 0 ? 1 : (i % 3 == 1 ? n : rnd.next(1, n)));
            rows.push_back({col, col});
        }
    } else if (mode == 3) {
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 3) == 0) {
                rows.push_back({1, n});
            } else {
                int width = rnd.next(max(1, n / 3), n);
                int l = rnd.next(1, n - width + 1);
                rows.push_back({l, l + width - 1});
            }
        }
    } else if (mode == 4) {
        int center = rnd.next(1, n);
        for (int i = 0; i < n; ++i) {
            center += rnd.next(-2, 2);
            center = min(n, max(1, center));
            int radius = rnd.next(0, max(1, n / 4));
            rows.push_back(centeredInterval(n, center, radius));
        }
    } else {
        for (int i = 0; i < n; ++i) {
            int pattern = rnd.next(0, 4);
            if (pattern == 0) {
                rows.push_back({1, rnd.next(1, n)});
            } else if (pattern == 1) {
                rows.push_back({rnd.next(1, n), n});
            } else if (pattern == 2) {
                int col = rnd.next(1, n);
                rows.push_back({col, col});
            } else if (pattern == 3) {
                rows.push_back({1, n});
            } else {
                rows.push_back(randomInterval(n));
            }
        }
    }

    println(n);
    for (const auto& row : rows) {
        println(row.first, row.second);
    }

    return 0;
}
