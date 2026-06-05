#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

static pair<int, int> elevatorThrough(int floor, int n) {
    int step = rnd.next(1, max(1, min(n, 30)));
    int start = floor - step * rnd.next(0, (floor - 1) / step);
    return {start, step};
}

static pair<int, int> elevatorAvoiding(int floor, int n) {
    for (int tries = 0; tries < 100; ++tries) {
        int x = rnd.next(1, n);
        int y = rnd.next(1, n);
        if (floor < x || (floor - x) % y != 0) return {x, y};
    }
    return {floor == 1 ? 2 : 1, n};
}

static void printCase(int n, vector<pair<int, int>> elevators, int a, int b) {
    shuffle(elevators.begin(), elevators.end());
    println(n, static_cast<int>(elevators.size()));
    for (auto [x, y] : elevators) println(x, y);
    println(a, b);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 80);
    if (mode == 1) n = rnd.next(3, 80);
    if (mode == 4) n = rnd.next(9, 80);
    if (mode == 5) n = rnd.next(50000, 100000);

    vector<pair<int, int>> elevators;
    int a = rnd.next(1, n);
    int b = rnd.next(1, n - 1);
    if (b >= a) ++b;

    if (mode == 0) {
        a = rnd.next(1, n);
        b = rnd.next(1, n - 1);
        if (b >= a) ++b;
        elevators.push_back({min(a, b), abs(a - b)});
    } else if (mode == 1) {
        int mid = rnd.next(1, n);
        a = rnd.next(1, n);
        while (a == mid) a = rnd.next(1, n);
        b = rnd.next(1, n);
        while (b == a || b == mid) b = rnd.next(1, n);
        elevators.push_back(elevatorThrough(a, n));
        elevators.push_back(elevatorThrough(mid, n));
        elevators.push_back(elevatorThrough(b, n));
        elevators[0] = {min(a, mid), abs(a - mid)};
        elevators[1] = {min(mid, b), abs(mid - b)};
    } else if (mode == 2) {
        a = rnd.next(1, n);
        b = rnd.next(1, n - 1);
        if (b >= a) ++b;
        int m = rnd.next(1, 8);
        for (int i = 0; i < m; ++i) {
            int x = rnd.next(1, n);
            int y = rnd.next(max(1, n / 2), n);
            elevators.push_back({x, y});
        }
    } else if (mode == 3) {
        int m = rnd.next(4, 12);
        int base = rnd.next(1, min(n, 10));
        for (int i = 0; i < m; ++i) {
            int y = rnd.next(1, max(1, min(n, 20)));
            elevators.push_back({base, y});
        }
        a = base;
        b = rnd.next(1, n - 1);
        if (b >= a) ++b;
    } else if (mode == 4) {
        int chainLength = rnd.next(3, 8);
        vector<int> floors;
        floors.push_back(rnd.next(1, n));
        while (static_cast<int>(floors.size()) <= chainLength) {
            int next = rnd.next(1, n);
            if (find(floors.begin(), floors.end(), next) == floors.end()) floors.push_back(next);
        }
        a = floors.front();
        b = floors.back();
        for (int i = 0; i < chainLength; ++i) {
            elevators.push_back({min(floors[i], floors[i + 1]), abs(floors[i] - floors[i + 1])});
        }
    } else {
        a = rnd.next(n - 1000, n);
        b = rnd.next(1, 1000);
        elevators.push_back({1, 1});
        elevators.push_back(elevatorThrough(a, n));
        elevators.push_back(elevatorThrough(b, n));
    }

    int targetM = rnd.next(static_cast<int>(elevators.size()), min(100, static_cast<int>(elevators.size()) + 15));
    while (static_cast<int>(elevators.size()) < targetM) {
        if (rnd.next(0, 3) == 0) {
            elevators.push_back(elevatorAvoiding(rnd.any(vector<int>{a, b}), n));
        } else {
            elevators.push_back({rnd.next(1, n), rnd.next(1, n)});
        }
    }

    printCase(n, elevators, a, b);
    return 0;
}
