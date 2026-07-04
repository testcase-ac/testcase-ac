#include "testlib.h"

#include <algorithm>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int h;
    int m;
    int n;
    if (mode == 4) {
        h = rnd.next(20, 50);
        m = rnd.next(20, 50);
        n = rnd.next(20, 50);
    } else {
        h = rnd.next(2, 8);
        m = rnd.next(2, 9);
        n = rnd.next(2, 9);
    }

    vector<vector<string>> maze(h, vector<string>(m, string(n, 'o')));
    vector<vector<vector<int>>> onPath(h, vector<vector<int>>(m, vector<int>(n, 0)));

    int r = rnd.next(0, m - 1);
    int c = rnd.next(0, n - 1);
    int sr = r;
    int sc = c;
    vector<tuple<int, int, int>> path;

    auto carve = [&](int z, int rr, int cc) {
        maze[z][rr][cc] = '.';
        onPath[z][rr][cc] = 1;
        path.push_back({z, rr, cc});
    };

    for (int z = 0; z < h; ++z) {
        carve(z, r, c);

        int segmentCount = (mode == 0 ? rnd.next(0, 1) : rnd.next(1, 4));
        for (int step = 0; step < segmentCount; ++step) {
            bool moveRow = rnd.next(0, 1);
            int targetR = rnd.next(0, m - 1);
            int targetC = rnd.next(0, n - 1);

            if (moveRow) {
                while (r != targetR) {
                    r += (targetR > r ? 1 : -1);
                    carve(z, r, c);
                }
                while (c != targetC) {
                    c += (targetC > c ? 1 : -1);
                    carve(z, r, c);
                }
            } else {
                while (c != targetC) {
                    c += (targetC > c ? 1 : -1);
                    carve(z, r, c);
                }
                while (r != targetR) {
                    r += (targetR > r ? 1 : -1);
                    carve(z, r, c);
                }
            }
        }
    }

    maze[0][sr][sc] = '1';
    maze[h - 1][r][c] = '2';

    int extraOpenPercent;
    if (mode == 0) {
        extraOpenPercent = rnd.next(0, 10);
    } else if (mode == 1) {
        extraOpenPercent = rnd.next(10, 30);
    } else if (mode == 2) {
        extraOpenPercent = rnd.next(35, 65);
    } else {
        extraOpenPercent = rnd.next(65, 95);
    }

    for (int z = 0; z < h; ++z) {
        for (int rr = 0; rr < m; ++rr) {
            for (int cc = 0; cc < n; ++cc) {
                if (onPath[z][rr][cc]) {
                    continue;
                }
                if (rnd.next(1, 100) <= extraOpenPercent) {
                    maze[z][rr][cc] = '.';
                }
            }
        }
    }

    println(h, m, n);
    for (int z = 0; z < h; ++z) {
        for (int rr = 0; rr < m; ++rr) {
            println(maze[z][rr]);
        }
    }

    return 0;
}
