#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using Point = pair<ll, ll>;

const ll MIN_COORD = -1000000000000LL;
const ll MAX_COORD = 1000000000000LL;

Point add(Point a, Point b) {
    return {a.first + b.first, a.second + b.second};
}

Point randomSmallPoint(int radius) {
    while (true) {
        Point p = {rnd.next(-radius, radius), rnd.next(-radius, radius)};
        if (p != Point{0, 0}) return p;
    }
}

Point randomExtremePoint() {
    vector<ll> values = {
        MIN_COORD,
        MIN_COORD + rnd.next(0, 5),
        -rnd.next(1, 10),
        rnd.next(1, 10),
        MAX_COORD - rnd.next(0, 5),
        MAX_COORD,
    };

    while (true) {
        Point p = {rnd.any(values), rnd.any(values)};
        if (p != Point{0, 0}) return p;
    }
}

void addUnique(vector<Point>& items, set<Point>& used, Point p) {
    if (p == Point{0, 0}) return;
    if (p.first < MIN_COORD || p.first > MAX_COORD) return;
    if (p.second < MIN_COORD || p.second > MAX_COORD) return;
    if (used.insert(p).second) items.push_back(p);
}

void fillItems(vector<Point>& items, int target, int radius) {
    set<Point> used(items.begin(), items.end());
    while ((int)items.size() < target) {
        Point p;
        if (rnd.next(100) < 15) {
            p = randomExtremePoint();
        } else {
            p = randomSmallPoint(radius);
        }
        addUnique(items, used, p);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int k = rnd.next(1, 5);
    int n = rnd.next(1, 12);
    vector<Point> items;
    Point dest = randomSmallPoint(5);

    if (mode == 0) {
        k = rnd.next(1, 5);
        int dist = rnd.next(1, 5);
        int x = rnd.next(0, dist);
        dest = {x, dist - x};
        if (rnd.next(2)) dest.first = -dest.first;
        if (rnd.next(2)) dest.second = -dest.second;
    } else if (mode == 1) {
        k = rnd.next(2, 5);
        Point item = randomSmallPoint(8);
        Point walk = {0, 0};
        if (k > 2) walk = randomSmallPoint(k - 2);
        dest = add(item, walk);
        if (dest == Point{0, 0}) dest = item;
        items.push_back(item);
    } else if (mode == 2) {
        k = rnd.next(4, 5);
        Point a = randomSmallPoint(8);
        Point b = randomSmallPoint(8);
        while (b == a) b = randomSmallPoint(8);
        dest = add(a, b);
        if (dest == Point{0, 0}) dest = add(a, {1, 0});
        items.push_back(a);
        items.push_back(b);
    } else if (mode == 3) {
        k = rnd.next(1, 5);
        dest = randomSmallPoint(12);
        while (abs(dest.first) + abs(dest.second) <= k) dest = randomSmallPoint(12);
        items.push_back({dest.first + rnd.next(2, 5), dest.second + rnd.next(2, 5)});
    } else if (mode == 4) {
        k = 5;
        Point a = randomSmallPoint(8);
        Point b = randomSmallPoint(8);
        while (b == a) b = randomSmallPoint(8);
        vector<Point> step = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        dest = add(add(a, b), rnd.any(step));
        if (dest == Point{0, 0}) dest = add(add(a, b), {1, 0});
        items.push_back(a);
        items.push_back(b);
    } else if (mode == 5) {
        k = rnd.next(1, 5);
        dest = randomExtremePoint();
        items.push_back({dest.first == MIN_COORD ? MAX_COORD : MIN_COORD,
                         dest.second == MIN_COORD ? MAX_COORD : MIN_COORD});
    } else if (mode == 6) {
        k = rnd.next(2, 5);
        Point item = randomExtremePoint();
        dest = item;
        items.push_back(item);
    } else {
        k = rnd.next(1, 5);
        n = rnd.next(8, 30);
        dest = randomSmallPoint(20);
    }

    n = max(n, (int)items.size());
    fillItems(items, n, mode == 7 ? 30 : 10);
    shuffle(items.begin(), items.end());

    println((int)items.size(), k);
    for (Point item : items) println(item.first, item.second);
    println(dest.first, dest.second);
    return 0;
}
