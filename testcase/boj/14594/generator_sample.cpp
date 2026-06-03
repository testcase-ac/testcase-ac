#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    if (mode == 7) {
        n = 100;
    } else if (mode == 0) {
        n = rnd.next(2, 6);
    } else {
        n = rnd.next(2, 30);
    }

    vector<pair<int, int>> actions;

    if (mode == 0) {
        actions.clear();
    } else if (mode == 1) {
        int x = rnd.next(1, n - 1);
        int y = rnd.next(x + 1, n);
        int m = rnd.next(1, 100);
        for (int i = 0; i < m; ++i) actions.push_back({x, y});
    } else if (mode == 2) {
        int left = rnd.next(1, n - 1);
        int right = rnd.next(left + 1, n);
        int m = rnd.next(1, min(100, 3 * n));
        for (int i = 0; i < m; ++i) {
            int x = rnd.next(left, right - 1);
            int y = rnd.next(x + 1, right);
            actions.push_back({x, y});
        }
    } else if (mode == 3) {
        for (int x = 1; x < n && (int)actions.size() < 100; x += rnd.next(1, 3)) {
            int y = rnd.next(x + 1, min(n, x + rnd.next(1, 5)));
            actions.push_back({x, y});
            if (rnd.next(0, 3) == 0 && (int)actions.size() < 100) actions.push_back({x, y});
        }
    } else if (mode == 4) {
        int m = rnd.next(1, 100);
        for (int i = 0; i < m; ++i) {
            int x = rnd.next(1, n - 1);
            int y = rnd.next(x + 1, n);
            actions.push_back({x, y});
        }
    } else if (mode == 5) {
        actions.push_back({1, n});
        int m = rnd.next(1, 100);
        while ((int)actions.size() < m) {
            int x = rnd.next(1, n - 1);
            int y = rnd.next(x + 1, n);
            actions.push_back({x, y});
        }
    } else if (mode == 6) {
        int center = rnd.next(2, n);
        int m = rnd.next(1, min(100, 4 * n));
        for (int i = 0; i < m; ++i) {
            int x = rnd.next(1, center - 1);
            int y = rnd.next(center, n);
            actions.push_back({x, y});
        }
    } else {
        int m = rnd.next(80, 100);
        for (int i = 0; i < m; ++i) {
            int span = rnd.next(1, min(20, n - 1));
            int x = rnd.next(1, n - span);
            actions.push_back({x, x + span});
        }
    }

    shuffle(actions.begin(), actions.end());

    println(n);
    println((int)actions.size());
    for (auto [x, y] : actions) println(x, y);

    return 0;
}
