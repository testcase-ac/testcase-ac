#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <stack>
#include <vector>

using namespace std;

bool canComplete(vector<int> cars) {
    reverse(cars.begin(), cars.end());

    stack<int> branch;
    int next = 1;
    for (int car : cars) {
        while (!branch.empty() && branch.top() == next) {
            branch.pop();
            ++next;
        }

        if (car == next) {
            ++next;
        } else {
            branch.push(car);
        }
    }

    while (!branch.empty() && branch.top() == next) {
        branch.pop();
        ++next;
    }

    return next == static_cast<int>(cars.size()) + 1;
}

vector<int> orderedCars(int n) {
    vector<int> cars(n);
    iota(cars.begin(), cars.end(), 1);
    return cars;
}

vector<int> randomPermutation(int n) {
    vector<int> cars = orderedCars(n);
    shuffle(cars.begin(), cars.end());
    return cars;
}

vector<int> findClassifiedPermutation(int n, bool wantCompletable) {
    for (int attempt = 0; attempt < 2000; ++attempt) {
        vector<int> cars = randomPermutation(n);
        if (canComplete(cars) == wantCompletable) {
            return cars;
        }
    }

    vector<int> fallback = orderedCars(n);
    if (!wantCompletable && n >= 3) {
        fallback = {1, 3, 2};
        for (int car = 4; car <= n; ++car) {
            fallback.push_back(car);
        }
    }
    return fallback;
}

vector<int> makeCase(int mode, int n) {
    vector<int> cars = orderedCars(n);

    if (n == 1) {
        return cars;
    }

    if (mode == 0) {
        return cars;
    }
    if (mode == 1) {
        reverse(cars.begin(), cars.end());
        return cars;
    }
    if (mode == 2) {
        int block = rnd.next(2, min(n, 6));
        for (int start = 0; start < n; start += block) {
            int finish = min(n, start + block);
            reverse(cars.begin() + start, cars.begin() + finish);
        }
        return cars;
    }
    if (mode == 3) {
        return findClassifiedPermutation(n, true);
    }
    return findClassifiedPermutation(n, false);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 10);
    println(t);

    bool emittedNoCandidate = false;
    for (int tc = 1; tc <= t; ++tc) {
        int n;
        if (tc == 1 && rnd.next(4) == 0) {
            n = 1;
        } else {
            n = rnd.next(2, 14);
        }

        int mode = rnd.next(0, 4);
        if (tc == t && !emittedNoCandidate && n >= 3) {
            mode = 4;
        }

        vector<int> cars = makeCase(mode, n);
        if (!canComplete(cars)) {
            emittedNoCandidate = true;
        }

        println(n);
        for (int car : cars) {
            println(car);
        }
    }

    return 0;
}
