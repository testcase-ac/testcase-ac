#include "testlib.h"
#include <algorithm>
#include <vector>
#include <utility>

using namespace std;

using Point = pair<int, int>;

Point clampPoint(int x, int y, int n) {
    if (x < 1) x = 1;
    if (x > n) x = n;
    if (y < 1) y = 1;
    if (y > n) y = n;
    return {x, y};
}

Point randomPoint(int n) {
    return {rnd.next(1, n), rnd.next(1, n)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int t;
    vector<Point> mold;
    vector<Point> inspect;

    if (mode == 0) {
        n = rnd.next(1, 5);
        t = rnd.any(vector<int>{1, 2, 9999, 10000});
    } else if (mode == 1) {
        n = rnd.next(2, 8);
        t = rnd.next(1, 4);
        Point p = randomPoint(n);
        int copies = rnd.next(1, min(6, n * n));
        for (int i = 0; i < copies; ++i) mold.push_back(p);
        copies = rnd.next(1, min(6, n * n));
        for (int i = 0; i < copies; ++i) inspect.push_back(p);
    } else if (mode == 2) {
        n = rnd.next(3, 12);
        t = rnd.next(1, 3);
        Point p = randomPoint(n);
        mold.push_back(p);
        vector<Point> moves;
        const int dx[8] = {1, 2, 2, 1, -1, -2, -2, -1};
        const int dy[8] = {2, 1, -1, -2, -2, -1, 1, 2};
        for (int i = 0; i < 8; ++i) {
            int x = p.first + dx[i];
            int y = p.second + dy[i];
            if (1 <= x && x <= n && 1 <= y && y <= n) moves.push_back({x, y});
        }
        if (moves.empty()) inspect.push_back(randomPoint(n));
        else inspect.push_back(rnd.any(moves));
        while ((int)inspect.size() < rnd.next(2, 7)) inspect.push_back(randomPoint(n));
    } else if (mode == 3) {
        n = rnd.next(4, 15);
        t = rnd.next(4, 20);
        int count = rnd.next(1, 8);
        for (int i = 0; i < count; ++i) mold.push_back(randomPoint(n));
        count = rnd.next(1, 10);
        for (int i = 0; i < count; ++i) inspect.push_back(randomPoint(n));
    } else if (mode == 4) {
        n = rnd.any(vector<int>{1, 2, 3, 300});
        t = rnd.next(9000, 10000);
        int count = rnd.next(0, min(8, n * n));
        for (int i = 0; i < count; ++i) mold.push_back(randomPoint(n));
        count = rnd.next(0, min(8, n * n));
        for (int i = 0; i < count; ++i) inspect.push_back(randomPoint(n));
    } else if (mode == 5) {
        n = rnd.next(5, 20);
        t = rnd.next(1, 25);
        vector<Point> corners = {{1, 1}, {1, n}, {n, 1}, {n, n}};
        shuffle(corners.begin(), corners.end());
        int count = rnd.next(1, 4);
        for (int i = 0; i < count; ++i) mold.push_back(corners[i]);
        for (Point p : corners) inspect.push_back(p);
        while ((int)inspect.size() < rnd.next(5, 12)) inspect.push_back(randomPoint(n));
    } else {
        n = rnd.next(8, 25);
        t = rnd.next(1, 10000);
        Point center = {rnd.next(3, n - 2), rnd.next(3, n - 2)};
        int radius = rnd.next(0, 3);
        for (int dx = -radius; dx <= radius; ++dx) {
            for (int dy = -radius; dy <= radius; ++dy) {
                if (rnd.next(0, 1)) mold.push_back(clampPoint(center.first + dx, center.second + dy, n));
            }
        }
        if (mold.empty()) mold.push_back(center);
        int count = rnd.next(1, 12);
        for (int i = 0; i < count; ++i) {
            int x = center.first + rnd.next(-5, 5);
            int y = center.second + rnd.next(-5, 5);
            inspect.push_back(clampPoint(x, y, n));
        }
    }

    println(n, (int)mold.size(), (int)inspect.size(), t);
    for (Point p : mold) println(p.first, p.second);
    for (Point p : inspect) println(p.first, p.second);

    return 0;
}
