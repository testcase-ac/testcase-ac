#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

namespace {

int randomY(int mode) {
    if (mode == 0) return rnd.next(0, 100000);
    if (mode == 1) return rnd.any(vector<int>{0, 1, 99999, 100000});
    if (mode == 2) return rnd.next(0, 200);
    return rnd.next(99800, 100000);
}

vector<int> uniqueXValues(int n, int mode) {
    set<int> used;
    vector<int> xs;

    if (mode == 0) {
        int start = rnd.next(0, 100000 - n + 1);
        for (int i = 0; i < n; ++i) xs.push_back(start + i);
    } else if (mode == 1) {
        xs.push_back(0);
        if (n > 1) xs.push_back(100000);
        used.insert(xs.begin(), xs.end());
        while ((int)xs.size() < n) {
            int x = rnd.next(1, 99999);
            if (used.insert(x).second) xs.push_back(x);
        }
    } else if (mode == 2) {
        int base = rnd.next(0, max(0, 100000 - 3 * n));
        for (int i = 0; i < n; ++i) xs.push_back(base + 3 * i + rnd.next(0, 1));
    } else {
        while ((int)xs.size() < n) {
            int x = rnd.next(0, 100000);
            if (used.insert(x).second) xs.push_back(x);
        }
    }

    sort(xs.begin(), xs.end());
    return xs;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 0) {
        n = rnd.next(1, 2);
    } else if (mode == 1) {
        n = rnd.next(3, 8);
    } else if (mode == 6) {
        n = rnd.next(120, 1000);
    } else {
        n = rnd.next(9, 60);
    }

    vector<int> xs = uniqueXValues(n, rnd.next(0, 3));
    vector<pair<int, int>> points;

    for (int i = 0; i < n; ++i) {
        int y;
        if (mode == 2) {
            y = (i % 2 == 0) ? rnd.next(0, 200) : rnd.next(99800, 100000);
        } else if (mode == 3) {
            int mid = n == 1 ? 0 : min(i, n - 1 - i);
            y = min(100000, mid * rnd.next(100, 800) + rnd.next(0, 50));
        } else if (mode == 4) {
            y = min(100000, max(0, 100000 - i * rnd.next(100, 900) + rnd.next(-50, 50)));
        } else {
            y = randomY(rnd.next(0, 3));
        }
        points.push_back({xs[i], y});
    }

    if (rnd.next(0, 1)) {
        shuffle(points.begin(), points.end());
    }

    println(n);
    for (const auto& point : points) {
        println(point.first, point.second);
    }

    return 0;
}
