#include "testlib.h"

#include <algorithm>
#include <vector>
using namespace std;

int boundedSum(const vector<int>& a, int count) {
    int sum = 0;
    for (int i = 0; i < count; ++i) sum += a[i];
    return min(sum, 100000);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, 24);
        if (tc == t - 1) n = rnd.next(30, 60);

        vector<int> a(n);
        int b = 1;

        if (mode == 0) {
            for (int& x : a) x = rnd.next(1, 30);
            b = rnd.next(boundedSum(a, n), 100000);
        } else if (mode == 1) {
            for (int& x : a) x = rnd.next(200, 1000);
            b = rnd.next(1, min(199, 100000));
        } else if (mode == 2) {
            int cheap = rnd.next(1, 20);
            int expensive = rnd.next(cheap + 1, 1000);
            int cheapCount = rnd.next(1, n);
            fill(a.begin(), a.begin() + cheapCount, cheap);
            fill(a.begin() + cheapCount, a.end(), expensive);
            b = min(100000, cheap * cheapCount);
        } else if (mode == 3) {
            for (int& x : a) x = rnd.next(1, 1000);
            sort(a.begin(), a.end());
            int canBuy = rnd.next(0, n);
            b = canBuy == 0 ? rnd.next(1, max(1, a[0] - 1)) : boundedSum(a, canBuy);
            if (canBuy < n && b < 100000 && rnd.next(0, 1)) ++b;
        } else if (mode == 4) {
            int base = rnd.next(1, 100);
            for (int i = 0; i < n; ++i) a[i] = min(1000, base + rnd.next(0, 5) * rnd.next(0, 20));
            sort(a.begin(), a.end());
            int canBuy = rnd.next(1, n);
            b = boundedSum(a, canBuy);
            if (canBuy < n) b = rnd.next(max(1, b - a[canBuy - 1] / 2), min(100000, b + a[canBuy]));
        } else {
            for (int& x : a) x = rnd.next(1, 1000);
            b = rnd.next(1, 100000);
        }

        shuffle(a.begin(), a.end());
        println(n, b);
        println(a);
    }

    return 0;
}
