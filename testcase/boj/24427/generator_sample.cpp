#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(5, 12);

    vector<vector<int>> a(n, vector<int>(n, 1));
    if (mode == 0) {
        int hi = rnd.next(3, 40);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = rnd.next(1, hi);
    } else if (mode == 1) {
        int base = rnd.next(1, 20);
        int rowStep = rnd.next(0, 7);
        int colStep = rnd.next(0, 7);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = min(100000, base + i * rowStep + j * colStep + rnd.next(0, 3));
    } else if (mode == 2) {
        int high = rnd.next(50000, 100000);
        int low = rnd.next(1, 20);
        int turn = rnd.next(0, n - 1);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                a[i][j] = low + rnd.next(0, 5);
                if ((i <= turn && j == 0) || (i == turn) || (i >= turn && j == n - 1))
                    a[i][j] = high - rnd.next(0, 100);
            }
        }
    } else if (mode == 3) {
        int hi = rnd.next(70, 200);
        int lo = rnd.next(1, 15);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = ((i + j) % 2 == 0 ? hi : lo) + rnd.next(0, 9);
    } else {
        int peaks = rnd.next(1, n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j)
                a[i][j] = rnd.next(1, 10);
        for (int k = 0; k < peaks; ++k)
            a[rnd.next(0, n - 1)][rnd.next(0, n - 1)] = rnd.next(1000, 100000);
    }

    vector<pair<int, int>> points;
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= n; ++c) {
            if ((r == 1 && c == 1) || (r == n && c == n))
                continue;
            points.push_back({r, c});
        }
    }
    shuffle(points.begin(), points.end());

    int maxP = min<int>(points.size(), rnd.next(1, 35));
    int p = rnd.next(1, maxP);
    points.resize(p);

    println(n);
    for (const auto& row : a)
        println(row);
    println(p);
    for (const auto& point : points)
        println(point.first, point.second);

    return 0;
}
