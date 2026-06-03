#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    int n = 1;
    long long k = 1;
    vector<string> s(2);

    auto init = [&](int len, char fill) {
        n = len;
        s[0] = string(n, fill);
        s[1] = string(n, fill);
    };

    auto chooseK = [&]() -> long long {
        int kMode = rnd.next(0, 4);
        if (kMode == 0) return 1;
        if (kMode == 1) return rnd.next(2, 8);
        if (kMode == 2) return rnd.next(9, 1000);
        if (kMode == 3) return rnd.next(1000000, 1000000000);
        return 1000000000LL;
    };

    if (mode == 0) {
        init(rnd.next(1, 25), '.');
        k = chooseK();
    } else if (mode == 1) {
        init(rnd.next(1, 12), '#');
        int roads = rnd.next(0, min(4, 2 * n));
        for (int t = 0; t < roads; ++t) {
            s[rnd.next(0, 1)][rnd.next(0, n - 1)] = '.';
        }
        k = chooseK();
    } else if (mode == 2) {
        init(rnd.next(2, 30), '#');
        int row = rnd.next(0, 1);
        for (int c = 0; c < n; ++c) {
            if (rnd.next(0, 4) == 0) row ^= 1;
            s[row][c] = '.';
            if (rnd.next(0, 5) == 0) s[row ^ 1][c] = '.';
        }
        k = chooseK();
    } else if (mode == 3) {
        init(rnd.next(2, 30), '.');
        for (int c = 0; c < n; ++c) {
            int row = (c + rnd.next(0, 1)) & 1;
            if (rnd.next(0, 2) != 0) s[row][c] = '#';
        }
        k = chooseK();
    } else if (mode == 4) {
        init(rnd.next(1, 30), '.');
        double obstacleProb = rnd.next(0.05, 0.80);
        for (int r = 0; r < 2; ++r) {
            for (int c = 0; c < n; ++c) {
                if (rnd.next() < obstacleProb) s[r][c] = '#';
            }
        }
        k = chooseK();
    } else if (mode == 5) {
        init(rnd.next(2, 30), '.');
        for (int c = 0; c < n; ++c) {
            if (c % 3 == 1) s[0][c] = '#';
            if (c % 3 == 2) s[1][c] = '#';
        }
        if (rnd.next(0, 1)) reverse(s[0].begin(), s[0].end());
        if (rnd.next(0, 1)) reverse(s[1].begin(), s[1].end());
        k = chooseK();
    } else if (mode == 6) {
        init(rnd.next(1, 20), '.');
        s[rnd.next(0, 1)][0] = '#';
        s[rnd.next(0, 1)][n - 1] = '#';
        for (int c = 1; c + 1 < n; ++c) {
            if (rnd.next(0, 3) == 0) s[rnd.next(0, 1)][c] = '#';
        }
        k = chooseK();
    } else {
        init(rnd.next(20, 80), '.');
        for (int c = 0; c < n; ++c) {
            int pattern = c % rnd.next(2, 6);
            if (pattern == 0 && rnd.next(0, 1)) s[0][c] = '#';
            if (pattern == 1 && rnd.next(0, 1)) s[1][c] = '#';
            if (rnd.next(0, 9) == 0) s[rnd.next(0, 1)][c] = '#';
        }
        k = chooseK();
    }

    println(n, k);
    println(s[0]);
    println(s[1]);

    return 0;
}
