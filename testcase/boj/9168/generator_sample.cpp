#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct MazeCase {
    int r;
    int c;
    vector<string> maze;
};

MazeCase makeCase() {
    while (true) {
        int r = rnd.next(4, 14);
        int c = rnd.next(4, 18);
        vector<string> maze(r, string(c, 'X'));
        vector<vector<bool>> protectedCell(r, vector<bool>(c, false));

        pair<int, int> start = {rnd.next(1, r - 2), rnd.next(1, c - 2)};
        pair<int, int> finish = {rnd.next(1, r - 2), rnd.next(1, c - 2)};
        if (start == finish) continue;

        auto openCell = [&](int row, int col) {
            maze[row][col] = ' ';
            protectedCell[row][col] = true;
        };

        openCell(start.first, start.second);
        if (start.first == finish.first || start.second == finish.second) {
            int rowStep = (finish.first > start.first) -
                          (finish.first < start.first);
            int colStep = (finish.second > start.second) -
                          (finish.second < start.second);
            for (int row = start.first, col = start.second;
                 row != finish.first || col != finish.second;) {
                row += rowStep;
                col += colStep;
                openCell(row, col);
            }
        } else {
            bool horizontalFirst =
                (finish.second > start.second && finish.first > start.first) ||
                (finish.second < start.second && finish.first < start.first);
            if (horizontalFirst) {
                int colStep = (finish.second > start.second) ? 1 : -1;
                for (int col = start.second; col != finish.second;) {
                    col += colStep;
                    openCell(start.first, col);
                }
                int rowStep = (finish.first > start.first) ? 1 : -1;
                for (int row = start.first; row != finish.first;) {
                    row += rowStep;
                    openCell(row, finish.second);
                }
            } else {
                int rowStep = (finish.first > start.first) ? 1 : -1;
                for (int row = start.first; row != finish.first;) {
                    row += rowStep;
                    openCell(row, start.second);
                }
                int colStep = (finish.second > start.second) ? 1 : -1;
                for (int col = start.second; col != finish.second;) {
                    col += colStep;
                    openCell(finish.first, col);
                }
            }
        }

        int extraOpenChance = rnd.next(15, 70);
        for (int i = 1; i + 1 < r; ++i) {
            for (int j = 1; j + 1 < c; ++j) {
                if (!protectedCell[i][j] &&
                    rnd.next(0, 99) < extraOpenChance) {
                    maze[i][j] = ' ';
                }
            }
        }

        maze[start.first][start.second] = 'S';
        maze[finish.first][finish.second] = 'F';
        return {r, c, maze};
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(3, 8);
    println(n);
    for (int caseIndex = 0; caseIndex < n; ++caseIndex) {
        MazeCase tc = makeCase();
        println(tc.r, tc.c);
        for (const string& row : tc.maze) {
            println(row);
        }
    }

    return 0;
}
