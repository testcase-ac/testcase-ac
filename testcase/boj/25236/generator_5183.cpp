#include "testlib.h"
#include <vector>
#include <algorithm>
#include <array>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of trees
    int n = rnd.next(3, 10);
    // Grid dimensions chosen to ensure at least n distinct positions
    int Xmax = rnd.next(1, n);
    int minY = (n + Xmax - 1) / Xmax;
    int Ymax = rnd.next(minY, minY + 5);
    // Height bounds
    int Hbound = rnd.next(1, 100);
    int Hmin = rnd.next(1, Hbound);
    int Hmax2 = rnd.next(Hmin, Hbound);
    // Generate all possible grid positions, shuffle and take first n
    vector<pair<int,int>> coords;
    for (int x = 1; x <= Xmax; x++)
        for (int y = 1; y <= Ymax; y++)
            coords.emplace_back(x, y);
    shuffle(coords.begin(), coords.end());
    coords.resize(n);
    // Assign heights with mixed distributions for diversity
    vector<int> heights(n);
    int range = Hmax2 - Hmin + 1;
    for (int i = 0; i < n; i++) {
        if (rnd.next(0, 1) == 0) {
            // uniform
            heights[i] = rnd.next(Hmin, Hmax2);
        } else {
            // weighted (skewed) distribution
            int t = rnd.next(-2, 2);
            heights[i] = rnd.wnext(range, t) + Hmin;
        }
    }
    // Number of queries
    int q = rnd.next(1, 20);
    vector<array<int,4>> qs;
    qs.reserve(q);
    // Generate queries, some tight within [1..Xmax/Ymax], some extended
    for (int i = 0; i < q; i++) {
        int x_low, x_high, y_low, y_high;
        if (rnd.next(0, 1) == 0) {
            x_low = rnd.next(1, Xmax);
            x_high = rnd.next(x_low, Xmax);
        } else {
            int low = rnd.next(1, Xmax + 5);
            x_low = low;
            x_high = rnd.next(low, Xmax + 5);
        }
        if (rnd.next(0, 1) == 0) {
            y_low = rnd.next(1, Ymax);
            y_high = rnd.next(y_low, Ymax);
        } else {
            int low = rnd.next(1, Ymax + 5);
            y_low = low;
            y_high = rnd.next(low, Ymax + 5);
        }
        qs.push_back({x_low, y_low, x_high, y_high});
    }
    // Output the test case
    println(n, q);
    for (int i = 0; i < n; i++) {
        println(coords[i].first, coords[i].second, heights[i]);
    }
    for (auto &qr : qs) {
        println(qr[0], qr[1], qr[2], qr[3]);
    }
    return 0;
}
