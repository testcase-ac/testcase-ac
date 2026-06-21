#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct Point {
    int r;
    int c;
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = 1, m = 1;
    vector<string> grid;

    if (mode == 0) {
        n = rnd.next(1, 3);
        m = rnd.next(1, 3);
        grid.assign(n, string(m, rnd.any(string("SGM"))));
    } else {
        n = rnd.next(2, 12);
        m = rnd.next(2, 12);
        grid.assign(n, string(m, 'M'));
    }

    if (mode == 1) {
        string chars = "SGM";
        int a = rnd.next(1, 8), b = rnd.next(1, 8);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = chars[(a * i + b * j + rnd.next(0, 1)) % 3];
            }
        }
    } else if (mode == 2) {
        char dominant = rnd.any(string("SGM"));
        string others;
        for (char ch : string("SGM")) {
            if (ch != dominant) others += ch;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.next(0, 99) < 65 ? dominant : rnd.any(others);
            }
        }
    } else if (mode == 3) {
        string rowPattern = rnd.next(0, 1) ? "SGM" : "MSG";
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rowPattern[(i + j) % 3];
            }
        }
    } else if (mode == 4 || mode == 5) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                grid[i][j] = rnd.any(string("SGM"));
            }
        }

        vector<Point> dirs;
        for (int dr = -1; dr <= 1; ++dr) {
            for (int dc = -1; dc <= 1; ++dc) {
                if (dr != 0 || dc != 0) dirs.push_back({dr, dc});
            }
        }
        int planted = rnd.next(1, min(8, n * m));
        for (int t = 0; t < planted; ++t) {
            shuffle(dirs.begin(), dirs.end());
            bool placed = false;
            for (Point d : dirs) {
                vector<Point> starts;
                for (int r = 0; r < n; ++r) {
                    for (int c = 0; c < m; ++c) {
                        int r2 = r + 2 * d.r, c2 = c + 2 * d.c;
                        if (0 <= r2 && r2 < n && 0 <= c2 && c2 < m) {
                            starts.push_back({r, c});
                        }
                    }
                }
                if (starts.empty()) continue;
                Point p = rnd.any(starts);
                bool mushroomFirst = rnd.next(0, 1);
                grid[p.r][p.c] = mushroomFirst ? 'M' : 'S';
                grid[p.r + d.r][p.c + d.c] = 'G';
                grid[p.r + 2 * d.r][p.c + 2 * d.c] = mushroomFirst ? 'S' : 'M';
                placed = true;
                break;
            }
            if (!placed) break;
        }
    }

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
