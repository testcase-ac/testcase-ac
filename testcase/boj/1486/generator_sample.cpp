#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char encodeHeight(int h) {
    if (h < 26) return char('A' + h);
    return char('a' + h - 26);
}

int clampHeight(int h) {
    return max(0, min(51, h));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(6);
    int n = rnd.next(1, 9);
    int m = rnd.next(1, 9);

    if (mode == 0) {
        n = 1;
        m = rnd.next(1, 12);
    } else if (mode == 1) {
        n = rnd.next(1, 12);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 5);
        m = rnd.next(2, 5);
    }

    int t = rnd.next(1, 52);
    int d;
    if (mode == 3) {
        d = rnd.next(1, 80);
    } else if (mode == 4) {
        d = rnd.next(1000, 1000000);
    } else {
        d = rnd.next(1, 5000);
    }

    vector<string> grid(n, string(m, 'A'));
    int base = rnd.next(0, 51);

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            int h;
            if (mode == 0 || mode == 1) {
                int step = rnd.next(-2, 5);
                h = base + (i + j) * step + rnd.next(-1, 1);
            } else if (mode == 2) {
                h = ((i + j) % 2 == 0) ? rnd.next(0, 25) : rnd.next(26, 51);
            } else if (mode == 3) {
                h = base + abs(i - j) * rnd.next(0, 4) + rnd.next(-2, 2);
            } else if (mode == 4) {
                h = rnd.next(20, 51);
            } else {
                int slope = rnd.next(-4, 4);
                h = base + i * rnd.next(-3, 3) + j * slope + rnd.next(-3, 3);
            }
            grid[i][j] = encodeHeight(clampHeight(h));
        }
    }

    if (rnd.next(4) == 0) grid[0][0] = encodeHeight(rnd.next(0, 5));
    if (rnd.next(5) == 0) t = rnd.next(1, 5);

    println(n, m, t, d);
    for (const string& row : grid) println(row);

    return 0;
}
