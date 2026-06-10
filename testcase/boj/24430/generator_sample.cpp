#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(5, 14);
    if (mode == 5) {
        n = rnd.next(15, 30);
    }

    vector<vector<int>> a(n + 1, vector<int>(n + 1, 1));

    if (mode == 1) {
        int bend = rnd.next(1, n);
        for (int c = 1; c <= n; ++c) {
            a[bend][c] = 2;
        }
        for (int r = bend; r <= n; ++r) {
            a[r][n] = 2;
        }
    } else if (mode == 2) {
        int band = rnd.next(0, 2);
        for (int r = 1; r <= n; ++r) {
            for (int c = 1; c <= n; ++c) {
                if (abs(r - c) <= band) {
                    a[r][c] = 2;
                }
            }
        }
    } else if (mode == 3) {
        for (int r = 1; r <= n; ++r) {
            for (int c = 1; c <= n; ++c) {
                if ((r + c + rnd.next(0, 1)) % 2 == 0) {
                    a[r][c] = 2;
                }
            }
        }
    } else if (mode == 4) {
        int twos = rnd.next(n, min(n * n, 3 * n));
        while (twos--) {
            a[rnd.next(1, n)][rnd.next(1, n)] = 2;
        }
    } else if (mode == 5) {
        for (int r = 1; r <= n; ++r) {
            for (int c = 1; c <= n; ++c) {
                a[r][c] = rnd.next(1, 2);
            }
        }
    }

    vector<pair<int, int>> cells;
    vector<pair<int, int>> preferred;
    for (int r = 1; r <= n; ++r) {
        for (int c = 1; c <= n; ++c) {
            if ((r == 1 && c == 1) || (r == n && c == n)) {
                continue;
            }
            cells.push_back({r, c});
            if (r == 1 || c == n || r == c || a[r][c] == 2) {
                preferred.push_back({r, c});
            }
        }
    }

    shuffle(cells.begin(), cells.end());
    shuffle(preferred.begin(), preferred.end());

    int maxP = min<int>(cells.size(), max(1, 3 * n));
    int p = rnd.next(1, maxP);
    vector<pair<int, int>> points;
    set<pair<int, int>> used;

    if (!preferred.empty() && rnd.next(0, 1)) {
        int takePreferred = rnd.next(1, min<int>(p, preferred.size()));
        for (auto cell : preferred) {
            if ((int)points.size() == takePreferred) {
                break;
            }
            if (used.insert(cell).second) {
                points.push_back(cell);
            }
        }
    }

    for (auto cell : cells) {
        if ((int)points.size() == p) {
            break;
        }
        if (used.insert(cell).second) {
            points.push_back(cell);
        }
    }

    shuffle(points.begin(), points.end());

    println(n);
    for (int r = 1; r <= n; ++r) {
        vector<int> row;
        for (int c = 1; c <= n; ++c) {
            row.push_back(a[r][c]);
        }
        println(row);
    }

    println((int)points.size());
    for (auto [r, c] : points) {
        println(r, c);
    }

    return 0;
}
