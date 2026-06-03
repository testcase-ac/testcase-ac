#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int sumMin(const vector<vector<int>>& times) {
    int total = 0;
    for (const auto& group : times) {
        total += *min_element(group.begin(), group.end());
    }
    return total;
}

int sumAll(const vector<vector<int>>& times) {
    int total = 0;
    for (const auto& group : times) {
        total += accumulate(group.begin(), group.end(), 0);
    }
    return total;
}

int clampM(int value) {
    return max(1, min(10000, value));
}

void printCase(int n, int m, const vector<vector<int>>& times) {
    println(n, m);

    vector<int> d(n);
    for (int i = 0; i < n; ++i) {
        d[i] = static_cast<int>(times[i].size());
    }
    println(d);

    for (const auto& group : times) {
        println(group);
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n;
    int m;
    vector<vector<int>> times;

    if (mode == 0) {
        n = 1;
        int d = rnd.next(1, 30);
        times.assign(1, {});
        int low = rnd.next(1, 500);
        int high = rnd.next(low, min(1000, low + rnd.next(0, 500)));
        for (int i = 0; i < d; ++i) {
            times[0].push_back(rnd.next(low, high));
        }
        m = rnd.next(1, 10000);
    } else if (mode == 1) {
        n = rnd.next(2, 18);
        times.assign(n, {});
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(1, 5);
            int base = rnd.next(20, 70);
            for (int j = 0; j < d; ++j) {
                times[i].push_back(rnd.next(base, min(1000, base + 60)));
            }
        }
        m = clampM(sumMin(times) - rnd.next(1, min(20, sumMin(times))));
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        times.assign(n, {});
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(1, 4);
            int base = rnd.next(1, 20);
            times[i].push_back(base);
            for (int j = 1; j < d; ++j) {
                times[i].push_back(rnd.next(base, min(1000, base + 40)));
            }
            shuffle(times[i].begin(), times[i].end());
        }
        m = clampM(sumMin(times));
    } else if (mode == 3) {
        n = rnd.next(3, 25);
        times.assign(n, {});
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(1, 3);
            for (int j = 0; j < d; ++j) {
                times[i].push_back(rnd.next(1, 30));
            }
        }
        int lo = sumMin(times);
        int hi = min(10000, sumAll(times));
        m = rnd.next(clampM(lo), max(clampM(lo), hi));
    } else if (mode == 4) {
        n = rnd.next(8, 40);
        times.assign(n, {});
        for (int i = 0; i < n; ++i) {
            int d = rnd.next(1, 2);
            int small = rnd.next(1, 9);
            times[i].push_back(small);
            if (d == 2) {
                times[i].push_back(rnd.next(small + 1, min(1000, small + rnd.next(10, 100))));
            }
            shuffle(times[i].begin(), times[i].end());
        }
        int lo = sumMin(times);
        m = clampM(lo + rnd.next(0, 120));
    } else {
        n = rnd.next(2, 10);
        times.assign(n, {});
        int remaining = rnd.next(n, 80);
        for (int i = 0; i < n; ++i) {
            int leftGroups = n - i - 1;
            int d = (i + 1 == n) ? remaining : rnd.next(1, remaining - leftGroups);
            remaining -= d;

            int low = rnd.next(1, 80);
            int high = rnd.next(low, min(1000, low + rnd.next(0, 250)));
            for (int j = 0; j < d; ++j) {
                times[i].push_back(rnd.next(low, high));
            }
        }
        int lo = sumMin(times);
        int hi = min(10000, sumAll(times));
        m = rnd.next(clampM(max(1, lo - rnd.next(0, 40))), max(clampM(lo), hi));
    }

    printCase(n, m, times);
    return 0;
}
