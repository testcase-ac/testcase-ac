#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int m = rnd.next(1, 12);
    int n = rnd.next(1, 12);
    if (mode == 1) {
        m = rnd.next(1, 3);
        n = rnd.next(8, 18);
    } else if (mode == 2) {
        m = rnd.next(8, 18);
        n = rnd.next(1, 3);
    } else if (mode == 5) {
        m = rnd.next(2, 8);
        n = rnd.next(2, 8);
    }

    vector<vector<long long>> elevation(m, vector<long long>(n, 0));
    long long base = rnd.next(0, 1000);

    if (mode == 0) {
        long long stepRow = rnd.next(0, 30);
        long long stepCol = rnd.next(0, 30);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                elevation[i][j] = base + stepRow * i + stepCol * j + rnd.next(0, 5);
            }
        }
    } else if (mode == 1 || mode == 2) {
        long long high = rnd.next(100000, 1000000000);
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                int k = mode == 1 ? j : i;
                elevation[i][j] = min(1000000000LL, base + 1LL * k * rnd.next(1, 70));
            }
        }
        elevation[rnd.next(0, m - 1)][rnd.next(0, n - 1)] = high;
    } else if (mode == 3) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                elevation[i][j] = rnd.next(0, 200);
            }
        }
        int barrierRow = rnd.next(0, m - 1);
        long long barrier = rnd.next(1000, 1000000);
        for (int j = 0; j < n; ++j) {
            elevation[barrierRow][j] = barrier + rnd.next(0, 20);
        }
    } else if (mode == 4) {
        vector<long long> levels = {0, 1, 2, 999999999LL, 1000000000LL};
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                elevation[i][j] = rnd.any(levels);
            }
        }
    } else {
        long long value = rnd.next(0, 50);
        for (int i = 0; i < m; ++i) {
            if (i % 2 == 0) {
                for (int j = 0; j < n; ++j) {
                    elevation[i][j] = value;
                    value += rnd.next(0, 25);
                }
            } else {
                for (int j = n - 1; j >= 0; --j) {
                    elevation[i][j] = value;
                    value += rnd.next(0, 25);
                }
            }
        }
    }

    vector<pair<int, int>> cells;
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j) {
            cells.push_back({i, j});
        }
    }
    shuffle(cells.begin(), cells.end());

    vector<vector<int>> waypoint(m, vector<int>(n, 0));
    int waypointMode = rnd.next(0, 4);
    if (m == 1 && n == 1) {
        waypoint[0][0] = 1;
    } else if (waypointMode == 0) {
        waypoint[cells[0].first][cells[0].second] = 1;
    } else if (waypointMode == 1) {
        waypoint[0][0] = 1;
        waypoint[m - 1][n - 1] = 1;
    } else if (waypointMode == 2) {
        waypoint[0][0] = 1;
        waypoint[0][n - 1] = 1;
        waypoint[m - 1][0] = 1;
        waypoint[m - 1][n - 1] = 1;
    } else {
        int count = rnd.next(1, min<int>(m * n, 20));
        for (int i = 0; i < count; ++i) {
            waypoint[cells[i].first][cells[i].second] = 1;
        }
    }

    println(m, n);
    for (int i = 0; i < m; ++i) {
        println(elevation[i]);
    }
    for (int i = 0; i < m; ++i) {
        println(waypoint[i]);
    }

    return 0;
}
