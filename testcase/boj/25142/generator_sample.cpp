#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(4);
    int n = 0;
    int m = 0;

    if (mode == 0) {
        n = 1;
        m = rnd.next(2, 16);
    } else if (mode == 1) {
        n = rnd.next(2, 16);
        m = 1;
    } else if (mode == 2) {
        n = rnd.next(2, 8);
        m = rnd.next(2, 8);
    } else {
        n = rnd.next(8, 18);
        m = rnd.next(8, 18);
    }

    vector<string> grid(n, string(m, '#'));
    vector<pair<int, int>> path;

    int r = rnd.next(n);
    int c = rnd.next(m);
    path.push_back({r, c});
    grid[r][c] = '.';

    int targetR = rnd.next(n);
    int targetC = rnd.next(m);
    while (targetR == r && targetC == c) {
        targetR = rnd.next(n);
        targetC = rnd.next(m);
    }

    vector<int> verticalSteps(abs(targetR - r), targetR > r ? 1 : -1);
    vector<int> horizontalSteps(abs(targetC - c), targetC > c ? 1 : -1);

    while (!verticalSteps.empty() || !horizontalSteps.empty()) {
        bool takeVertical = horizontalSteps.empty() ||
                            (!verticalSteps.empty() && rnd.next(2) == 0);
        if (takeVertical) {
            r += verticalSteps.back();
            verticalSteps.pop_back();
        } else {
            c += horizontalSteps.back();
            horizontalSteps.pop_back();
        }
        path.push_back({r, c});
        grid[r][c] = '.';
    }

    double openProbability = mode <= 1 ? 0.0 : rnd.next(0.15, 0.65);
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            if (grid[i][j] == '#' && rnd.next() < openProbability) {
                grid[i][j] = '.';
            }
        }
    }

    if (mode == 3) {
        int extraWalks = rnd.next(2, 8);
        for (int walk = 0; walk < extraWalks; ++walk) {
            int cr = rnd.next(n);
            int cc = rnd.next(m);
            int len = rnd.next(3, 12);
            for (int step = 0; step < len; ++step) {
                grid[cr][cc] = '.';
                int dir = rnd.next(4);
                int nr = cr + (dir == 0) - (dir == 1);
                int nc = cc + (dir == 2) - (dir == 3);
                if (0 <= nr && nr < n && 0 <= nc && nc < m) {
                    cr = nr;
                    cc = nc;
                }
            }
        }
    }

    pair<int, int> start = path.front();
    pair<int, int> finish = path.back();
    grid[start.first][start.second] = 'S';
    grid[finish.first][finish.second] = 'F';

    println(n, m);
    for (const string& row : grid) {
        println(row);
    }

    return 0;
}
