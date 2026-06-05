#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n;
    int m;

    if (mode == 0) {
        n = rnd.next(1, 8);
        m = 1;
    } else if (mode == 1) {
        n = 2 * rnd.next(0, 7) + 1;
        m = n;
    } else {
        n = rnd.next(3, 25);
        vector<int> odd;
        for (int x = 1; x <= n; x += 2) {
            odd.push_back(x);
        }
        m = rnd.any(odd);
    }

    int starts = n - m + 1;
    vector<vector<long long>> bombs(starts, vector<long long>(starts, 0));

    long long maxBomb = 0;
    if (mode == 0) {
        maxBomb = rnd.any(vector<long long>{0, 1, 2, 10, 1000000000LL, 2147483648LL});
        for (int r = 0; r < starts; ++r) {
            for (int c = 0; c < starts; ++c) {
                bombs[r][c] = rnd.next(0LL, maxBomb);
            }
        }
    } else if (mode == 1) {
        bombs[0][0] = rnd.next(0LL, 2147483648LL);
    } else if (mode == 2) {
        int placed = rnd.next(1, min(8, starts * starts));
        for (int i = 0; i < placed; ++i) {
            int r = rnd.next(0, starts - 1);
            int c = rnd.next(0, starts - 1);
            bombs[r][c] += rnd.next(1, 30);
        }
    } else if (mode == 3) {
        for (int r = 0; r < starts; ++r) {
            for (int c = 0; c < starts; ++c) {
                if (rnd.next() < 0.70) {
                    bombs[r][c] = rnd.next(0, 20);
                }
            }
        }
    } else if (mode == 4) {
        for (int r = 0; r < starts; ++r) {
            for (int c = 0; c < starts; ++c) {
                if (r == 0 || c == 0 || r + 1 == starts || c + 1 == starts || r == c) {
                    bombs[r][c] = rnd.next(0, 12);
                }
            }
        }
    } else {
        for (int r = 0; r < starts; ++r) {
            for (int c = 0; c < starts; ++c) {
                bombs[r][c] = (r + c + rnd.next(0, 2)) % 3 == 0 ? rnd.next(0, 15) : 0;
            }
        }
    }

    vector<vector<long long>> diff(n + 1, vector<long long>(n + 1, 0));
    for (int r = 0; r < starts; ++r) {
        for (int c = 0; c < starts; ++c) {
            long long count = bombs[r][c];
            diff[r][c] += count;
            diff[r][c + m] -= count;
            diff[r + m][c] -= count;
            diff[r + m][c + m] += count;
        }
    }

    println(n, m);
    for (int r = 0; r < n; ++r) {
        vector<long long> row;
        row.reserve(n);
        for (int c = 0; c < n; ++c) {
            if (r > 0) {
                diff[r][c] += diff[r - 1][c];
            }
            if (c > 0) {
                diff[r][c] += diff[r][c - 1];
            }
            if (r > 0 && c > 0) {
                diff[r][c] -= diff[r - 1][c - 1];
            }
            row.push_back(-diff[r][c]);
        }
        println(row);
    }

    return 0;
}
