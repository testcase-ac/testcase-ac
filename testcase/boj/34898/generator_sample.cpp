#include "testlib.h"
#include <algorithm>
#include <tuple>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;
    int m = 0;
    vector<tuple<int, int, int>> imurae;

    auto addRandom = [&](int count, int aMax, int bMax, int cMin, int cMax) {
        for (int i = 0; i < count; ++i) {
            int a = rnd.next(0, aMax);
            int b = rnd.next(0, bMax);
            int c = rnd.next(cMin, cMax);
            imurae.emplace_back(a, b, c);
        }
    };

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = rnd.next(0, 25);
        addRandom(n, 30, 30, 0, 12);
    } else if (mode == 1) {
        n = rnd.next(4, 14);
        m = rnd.next(0, 40);
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, 60);
            int b = (i % 3 == 0) ? rnd.next(40, 120) : rnd.next(0, 20);
            int c = (i % 4 == 0) ? 0 : rnd.next(1, 20);
            imurae.emplace_back(a, b, c);
        }
    } else if (mode == 2) {
        n = rnd.next(5, 18);
        m = rnd.next(1, 100);
        for (int i = 0; i < n; ++i) {
            int c = rnd.next(max(0, m - 5), min(10000, m + 15));
            imurae.emplace_back(rnd.next(0, 200), rnd.next(0, 200), c);
        }
    } else if (mode == 3) {
        n = rnd.next(6, 20);
        int baseCost = rnd.next(0, 30);
        m = rnd.next(0, min(10000, baseCost * n + 10));
        for (int i = 0; i < n; ++i) {
            int a = rnd.next(0, 100);
            int b = rnd.next(0, 100);
            int c = rnd.next(max(0, baseCost - 2), min(10000, baseCost + 2));
            imurae.emplace_back(a, b, c);
        }
    } else if (mode == 4) {
        n = rnd.next(2, 10);
        m = rnd.any(vector<int>{0, 1, 9999, 10000});
        for (int i = 0; i < n; ++i) {
            int a = rnd.any(vector<int>{0, 1, 99999, 100000});
            int b = rnd.any(vector<int>{0, 1, 99999, 100000});
            int c = rnd.any(vector<int>{0, 1, 9999, 10000});
            imurae.emplace_back(a, b, c);
        }
    } else {
        n = rnd.next(15, 35);
        m = rnd.next(0, 250);
        addRandom(n, 1000, 1000, 0, 80);
    }

    shuffle(imurae.begin(), imurae.end());

    println(n, m);
    for (auto [a, b, c] : imurae) {
        println(a, b, c);
    }

    return 0;
}
