#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

pair<int, int> randomEmployee(int mode) {
    if (mode == 0) return {rnd.next(0, 36500), rnd.next(0, 100000000)};
    if (mode == 1) return {rnd.next(0, 3), rnd.next(0, 3)};
    if (mode == 2) return {rnd.any(vector<int>{0, 1, 36500}), rnd.any(vector<int>{0, 1, 100000000})};
    return {rnd.next(36000, 36500), rnd.next(99999980, 100000000)};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;
    int k;

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(n + 1, 100000);
        k = rnd.next(0, n - 1);
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        m = rnd.next(2, min(5, n + 3));
        k = rnd.next(0, n - 1);
    } else if (mode == 2) {
        n = rnd.next(6, 18);
        m = rnd.next(2, min(6, n));
        k = rnd.next(0, n - 1);
    } else if (mode == 3) {
        n = rnd.next(2, 10);
        m = rnd.any(vector<int>{2, 3, 100000});
        k = rnd.next(0, n - 1);
    } else {
        n = rnd.next(10, 30);
        m = rnd.next(2, min(10, n));
        k = rnd.next(0, n - 1);
    }

    vector<pair<int, int>> employees(n);

    if (mode == 2) {
        int baseD = rnd.next(0, 36500);
        int baseH = rnd.next(0, 100000000);
        for (int i = 0; i < n; ++i) employees[i] = {baseD, baseH};

        for (int i = 0; i < n; ++i) {
            int tweak = rnd.next(0, 2);
            if (tweak == 1) employees[i].first = max(0, baseD - rnd.next(0, 2));
            if (tweak == 2) employees[i].second = max(0, baseH - rnd.next(0, 2));
        }
    } else if (mode == 4) {
        for (int i = 0; i < n; ++i) employees[i] = randomEmployee(i % 4);
        for (int lane = 0; lane < m && lane < n; ++lane) {
            employees[lane] = {36500 - rnd.next(0, 2), 100000000 - rnd.next(0, 20)};
        }
    } else {
        int valueMode = rnd.next(0, 3);
        for (int i = 0; i < n; ++i) employees[i] = randomEmployee(valueMode);
    }

    if (rnd.next(0, 3) == 0) {
        employees[k] = randomEmployee(rnd.next(0, 3));
    }

    println(n, m, k);
    for (auto employee : employees) println(employee.first, employee.second);

    return 0;
}
