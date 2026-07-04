#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

const int MAX_X = 2000000000;

int randomValue() {
    int mode = rnd.next(0, 4);
    if (mode == 0) return rnd.any(vector<int>{0, 1, 2, 104, 105, 106, 4504, 4505, 4506});
    if (mode == 1) return rnd.next(0, 10000);
    if (mode == 2) return rnd.next(100000, 10000000);
    if (mode == 3) return MAX_X - rnd.next(0, 10000);
    return rnd.next(0, MAX_X);
}

pair<int, int> randomInterval() {
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int x = randomValue();
        return {x, x};
    }

    if (mode == 1) {
        int left = rnd.next(0, 10000);
        int right = min(MAX_X, left + rnd.next(0, 5000));
        return {left, right};
    }

    if (mode == 2) {
        int right = MAX_X - rnd.next(0, 10000);
        int left = max(0, right - rnd.next(0, 5000));
        return {left, right};
    }

    if (mode == 3) {
        int center = rnd.any(vector<int>{105, 4505, 1886676121, 2000000000});
        int left = max(0, center - rnd.next(0, 50));
        int right = min(MAX_X, center + rnd.next(0, 50));
        return {left, right};
    }

    if (mode == 4) {
        int left = randomValue();
        int width = rnd.next(0, 1000000);
        return {left, min(MAX_X, left + width)};
    }

    int left = rnd.next(0, MAX_X);
    int right = rnd.next(left, MAX_X);
    return {left, right};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<pair<int, int>> intervals;

    if (mode == 0) {
        // Exercise the validator-permitted empty input.
    } else if (mode == 1) {
        int n = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            int x = rnd.any(vector<int>{0, 1, 105, 4505, 5000, MAX_X});
            intervals.push_back({x, x});
        }
    } else if (mode == 2) {
        int n = rnd.next(3, 12);
        int start = rnd.next(0, 1000);
        for (int i = 0; i < n; ++i) {
            int left = start + i * rnd.next(1, 20);
            int right = min(MAX_X, left + rnd.next(0, 100));
            intervals.push_back({left, right});
        }
    } else if (mode == 3) {
        intervals.push_back({0, 0});
        intervals.push_back({0, MAX_X});
        intervals.push_back({MAX_X, MAX_X});
        int extra = rnd.next(0, 7);
        for (int i = 0; i < extra; ++i) intervals.push_back(randomInterval());
    } else if (mode == 4) {
        int n = rnd.next(8, 30);
        for (int i = 0; i < n; ++i) intervals.push_back(randomInterval());
    } else {
        int n = rnd.next(40, 100);
        for (int i = 0; i < n; ++i) {
            int left = randomValue();
            int right = rnd.next(left, MAX_X);
            intervals.push_back({left, right});
        }
    }

    shuffle(intervals.begin(), intervals.end());

    println((int)intervals.size());
    for (auto [left, right] : intervals) {
        println(left, right);
    }

    return 0;
}
