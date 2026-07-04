#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int pickL() {
    vector<int> special = {0, 1, 2, 3, 4, 10, 20, 29, (1 << 30) - 1};
    if (rnd.next(100) < 45) return rnd.any(special);
    return rnd.next(0, (1 << 30) - 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = 2;
    } else {
        n = rnd.next(3, 15);
    }

    int l = pickL();
    int s = rnd.next(1, n);
    int t = rnd.next(1, n);
    vector<vector<int>> nexts(n + 1, vector<int>(4, 1));

    if (mode == 0) {
        for (int j = 0; j < 4; ++j) nexts[1][j] = 1;
        s = t = 1;
    } else if (mode == 1) {
        for (int i = 1; i <= n; ++i) {
            int other = 3 - i;
            for (int j = 0; j < 4; ++j) nexts[i][j] = (rnd.next(100) < 55 ? other : i);
        }
    } else if (mode == 2) {
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 4; ++j) {
                nexts[i][j] = (rnd.next(100) < 70 ? i : rnd.next(1, n));
            }
        }
    } else if (mode == 3) {
        for (int i = 1; i <= n; ++i) {
            int forward = min(n, i + 1);
            int jump = rnd.next(i, n);
            nexts[i][0] = forward;
            nexts[i][1] = jump;
            nexts[i][2] = rnd.next(1, i);
            nexts[i][3] = rnd.next(1, n);
        }
        s = rnd.next(1, max(1, n / 2));
        t = rnd.next((n + 1) / 2, n);
    } else {
        int cluster = rnd.next(1, n);
        for (int i = 1; i <= n; ++i) {
            for (int j = 0; j < 4; ++j) {
                if (rnd.next(100) < 35) {
                    nexts[i][j] = cluster;
                } else {
                    nexts[i][j] = rnd.next(1, n);
                }
            }
        }
    }

    println(n, l);
    println(s, t);
    for (int i = 1; i <= n; ++i) {
        println(nexts[i][0], nexts[i][1], nexts[i][2], nexts[i][3]);
    }

    return 0;
}
