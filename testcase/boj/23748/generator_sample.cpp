#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 0;
    int x = 0;
    int y = 0;
    vector<pair<int, int>> customers;

    if (mode == 0) {
        n = rnd.next(1, 8);
        x = rnd.next(70, 100);
        y = rnd.next(70, 100);
        int maxX = rnd.next(n, x - 1);
        int maxY = rnd.next(n, y - 1);
        int remainingX = maxX;
        int remainingY = maxY;
        for (int i = 0; i < n; ++i) {
            int xi = (i == n - 1) ? remainingX : rnd.next(1, max(1, remainingX - (n - i - 1)));
            int yi = (i == n - 1) ? remainingY : rnd.next(1, max(1, remainingY - (n - i - 1)));
            remainingX -= xi;
            remainingY -= yi;
            customers.push_back({xi, yi});
        }
    } else if (mode == 1) {
        n = rnd.next(1, 10);
        x = rnd.next(1, 100);
        y = rnd.next(1, 100);
        int winner = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            if (i == winner) {
                customers.push_back({rnd.next(x, 100), rnd.next(y, 100)});
            } else {
                customers.push_back({rnd.next(1, max(1, x - 1)), rnd.next(1, max(1, y - 1))});
            }
        }
    } else if (mode == 2) {
        n = rnd.next(3, 14);
        x = rnd.next(20, 100);
        y = rnd.next(20, 100);
        int splitX = rnd.next(1, x - 1);
        int splitY = rnd.next(1, y - 1);
        customers.push_back({splitX, rnd.next(1, splitY)});
        customers.push_back({x - splitX, y - splitY});
        for (int i = 2; i < n; ++i) {
            customers.push_back({rnd.next(1, min(100, max(1, x / 2))), rnd.next(1, min(100, max(1, y / 2)))});
        }
    } else if (mode == 3) {
        n = rnd.next(6, 18);
        x = rnd.next(50, 100);
        y = rnd.next(50, 100);
        for (int i = 0; i < n; ++i) {
            if (i % 2 == 0) {
                customers.push_back({rnd.next(30, 100), rnd.next(1, 8)});
            } else {
                customers.push_back({rnd.next(1, 8), rnd.next(30, 100)});
            }
        }
        shuffle(customers.begin(), customers.end());
    } else if (mode == 4) {
        n = rnd.next(12, 30);
        x = rnd.next(1, 100);
        y = rnd.next(1, 100);
        int lo = rnd.next(1, 20);
        int hi = rnd.next(lo, 100);
        for (int i = 0; i < n; ++i) {
            customers.push_back({rnd.next(lo, hi), rnd.next(lo, hi)});
        }
    } else {
        n = rnd.next(35, 50);
        x = rnd.next(80, 100);
        y = rnd.next(80, 100);
        for (int i = 0; i < n; ++i) {
            int xi = (rnd.next(0, 3) == 0) ? rnd.next(50, 100) : rnd.next(1, 15);
            int yi = (rnd.next(0, 3) == 0) ? rnd.next(50, 100) : rnd.next(1, 15);
            customers.push_back({xi, yi});
        }
    }

    println(n, x, y);
    for (auto [xi, yi] : customers) {
        println(xi, yi);
    }

    return 0;
}
