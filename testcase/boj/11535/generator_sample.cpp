#include "testlib.h"

#include <algorithm>
#include <iostream>
#include <set>
#include <vector>
using namespace std;

static vector<int> makeConsecutive(int n, int c1) {
    vector<int> c;
    for (int i = 0; i < n; ++i) c.push_back(c1 - i);
    return c;
}

static vector<int> makeRandomCapacities(int n, int c1, int lo) {
    set<int> chosen;
    chosen.insert(c1);
    while ((int)chosen.size() < n) chosen.insert(rnd.next(lo, c1 - 1));

    vector<int> c(chosen.begin(), chosen.end());
    sort(c.rbegin(), c.rend());
    return c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 5);
    int c1 = 0;
    vector<int> capacities;

    if (mode == 0) {
        c1 = rnd.next(n, 10);
        capacities = makeConsecutive(n, c1);
    } else if (mode == 1) {
        c1 = rnd.next(50, 64);
        capacities = makeRandomCapacities(n, c1, 1);
    } else if (mode == 2) {
        c1 = rnd.next(max(n, 12), 32);
        int step = rnd.next(2, 6);
        capacities.push_back(c1);
        for (int i = 1; i < n; ++i) {
            int nextCapacity = max(1, capacities.back() - rnd.next(1, step));
            while (nextCapacity > 1 && capacities.back() - nextCapacity == 0) --nextCapacity;
            capacities.push_back(nextCapacity);
        }
        sort(capacities.rbegin(), capacities.rend());
        capacities.erase(unique(capacities.begin(), capacities.end()), capacities.end());
        while ((int)capacities.size() < n) {
            int value = rnd.next(1, c1 - 1);
            if (find(capacities.begin(), capacities.end(), value) == capacities.end()) {
                capacities.push_back(value);
            }
        }
        sort(capacities.rbegin(), capacities.rend());
    } else if (mode == 3) {
        c1 = rnd.next(8, 64);
        capacities = makeRandomCapacities(n, c1, max(1, c1 / 2));
    } else if (mode == 4) {
        c1 = rnd.next(6, 64);
        int base = rnd.next(1, max(1, c1 / 4));
        capacities.push_back(c1);
        for (int k = 1; (int)capacities.size() < n && k <= 8; ++k) {
            int value = base * k;
            if (value < c1 && find(capacities.begin(), capacities.end(), value) == capacities.end()) {
                capacities.push_back(value);
            }
        }
        while ((int)capacities.size() < n) {
            int value = rnd.next(1, c1 - 1);
            if (find(capacities.begin(), capacities.end(), value) == capacities.end()) {
                capacities.push_back(value);
            }
        }
        sort(capacities.rbegin(), capacities.rend());
    } else {
        c1 = rnd.next(2, 64);
        n = rnd.next(2, min(5, c1));
        capacities = makeRandomCapacities(n, c1, 1);
    }

    int targetMode = rnd.next(0, 3);
    int v;
    if (targetMode == 0) {
        v = rnd.next(1, capacities[0] - 1);
    } else if (targetMode == 1) {
        v = rnd.any(capacities);
        if (v == capacities[0]) v = rnd.next(1, capacities[0] - 1);
    } else {
        int delta = rnd.next(1, min(8, capacities[0] - 1));
        v = capacities[0] - delta;
    }

    cout << n;
    for (int c : capacities) {
        cout << ' ' << c;
    }
    cout << ' ' << v << '\n';

    return 0;
}
