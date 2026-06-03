#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int randomValue(int limit, bool allowZero = true) {
    int value = rnd.next(-limit, limit);
    if (!allowZero && value == 0) value = rnd.next(0, 1) ? 1 : -1;
    return value;
}

vector<int> randomRow(int n, int limit, bool allowZero = true) {
    vector<int> row(n);
    for (int& value : row) value = randomValue(limit, allowZero);
    return row;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n;
    vector<int> a, b;

    if (mode == 0) {
        n = 1;
        a = {randomValue(1000)};
        b = {randomValue(1000)};
    } else if (mode == 1) {
        n = rnd.next(2, 12);
        int valueA = rnd.next(1, 20) * (rnd.next(0, 1) ? 1 : -1);
        int valueB = rnd.next(1, 20) * (rnd.next(0, 1) ? 1 : -1);
        a.assign(n, valueA);
        b.assign(n, valueB);
    } else if (mode == 2) {
        n = rnd.next(3, 30);
        a.resize(n);
        b.resize(n);
        for (int i = 0; i < n; ++i) {
            int sign = (i % 2 == 0) ? 1 : -1;
            a[i] = sign * rnd.next(1, 1000);
            b[i] = -sign * rnd.next(1, 1000);
        }
        if (rnd.next(0, 1)) reverse(b.begin(), b.end());
    } else if (mode == 3) {
        n = rnd.next(5, 45);
        a.assign(n, 0);
        b.assign(n, 0);
        int filled = rnd.next(1, min(n, 8));
        for (int i = 0; i < filled; ++i) {
            a[rnd.next(0, n - 1)] = randomValue(1000, false);
            b[rnd.next(0, n - 1)] = randomValue(1000, false);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 25);
        a.resize(n);
        b.resize(n);
        for (int i = 0; i < n; ++i) {
            a[i] = rnd.next(0, 1) ? 1000 : -1000;
            b[i] = rnd.next(0, 1) ? 1000 : -1000;
        }
    } else if (mode == 5) {
        n = rnd.next(6, 60);
        a = randomRow(n, 50);
        b = randomRow(n, 50);
        int left = rnd.next(0, n / 3);
        int right = rnd.next(0, n / 3);
        for (int i = left; i < n - right; ++i) {
            a[i] = rnd.next(80, 300);
            b[n - 1 - i] = rnd.next(80, 300);
        }
    } else if (mode == 6) {
        n = rnd.next(20, 120);
        int limit = rnd.any(vector<int>{3, 10, 100, 1000});
        a = randomRow(n, limit);
        b = randomRow(n, limit);
    } else {
        n = rnd.next(1800, 2000);
        a = randomRow(n, 3);
        b = randomRow(n, 3);
    }

    println(n);
    println(a);
    println(b);
    return 0;
}
