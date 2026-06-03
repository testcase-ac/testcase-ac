#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 30);
    vector<pair<int, int>> segments;

    if (mode == 0) {
        int cur = rnd.next(-50, 0);
        for (int i = 0; i < n; ++i) {
            int len = rnd.next(1, 12);
            segments.push_back({cur, cur + len});
            cur += len + rnd.next(1, 8);
        }
    } else if (mode == 1) {
        int cur = rnd.next(-30, 10);
        int right = cur + rnd.next(1, 10);
        for (int i = 0; i < n; ++i) {
            int x = cur + rnd.next(0, 5);
            int y = max(x + 1, right + rnd.next(-4, 8));
            segments.push_back({x, y});
            cur = x + rnd.next(0, 4);
            right = max(right, y);
        }
    } else if (mode == 2) {
        int x = rnd.next(-20, 20);
        int y = x + rnd.next(1, 5);
        for (int i = 0; i < n; ++i) {
            y += rnd.next(1, 6);
            segments.push_back({x, y});
        }
    } else if (mode == 3) {
        int left = rnd.next(-100, -10);
        int right = rnd.next(10, 100);
        for (int i = 0; i < n; ++i) {
            int x = rnd.next(left, min(right - 1, left + 50));
            int y = rnd.next(max(x + 1, right - 50), right);
            segments.push_back({x, y});
        }
    } else if (mode == 4) {
        segments.push_back({-1000000000, 1000000000});
        for (int i = 1; i < n; ++i) {
            int x = rnd.next(-1000000000, 999999999);
            int y = rnd.next(x + 1, 1000000000);
            segments.push_back({x, y});
        }
    } else {
        int cur = rnd.next(-60, -20);
        for (int i = 0; i < n; ++i) {
            int x = cur + rnd.next(0, 4);
            int y = x + rnd.next(1, 20);
            segments.push_back({x, y});
            cur += rnd.next(0, 10);
        }
    }

    sort(segments.begin(), segments.end());

    println((int)segments.size());
    for (auto [x, y] : segments) {
        println(x, y);
    }

    return 0;
}
