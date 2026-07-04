#include "testlib.h"

#include <queue>
#include <string>
#include <utility>
#include <vector>

using namespace std;

bool hasNoLeftTurnPath(const vector<string>& maze, pair<int, int> start,
                       pair<int, int> finish) {
    const int r = static_cast<int>(maze.size());
    const int c = static_cast<int>(maze[0].size());
    const int dr[4] = {-1, 0, 1, 0};
    const int dc[4] = {0, 1, 0, -1};

    vector<vector<vector<bool>>> seen(
        r, vector<vector<bool>>(c, vector<bool>(4, false)));
    queue<pair<pair<int, int>, int>> q;

    for (int dir = 0; dir < 4; ++dir) {
        seen[start.first][start.second][dir] = true;
        q.push({start, dir});
    }

    while (!q.empty()) {
        auto current = q.front();
        q.pop();
        int row = current.first.first;
        int col = current.first.second;
        int dir = current.second;

        if (make_pair(row, col) == finish) {
            return true;
        }

        for (int nextDir : {dir, (dir + 1) % 4}) {
            int nextRow = row + dr[nextDir];
            int nextCol = col + dc[nextDir];
            if (nextRow < 0 || nextRow >= r || nextCol < 0 || nextCol >= c) {
                continue;
            }
            if (maze[nextRow][nextCol] == 'X' ||
                seen[nextRow][nextCol][nextDir]) {
                continue;
            }
            seen[nextRow][nextCol][nextDir] = true;
            q.push({{nextRow, nextCol}, nextDir});
        }
    }

    return false;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // CHECK: N has no written upper bound; cap total maze cells to keep inputs inspectable.
    int n = inf.readInt(1, 100000, "N");
    inf.readEoln();

    int totalCells = 0;
    for (int caseIndex = 1; caseIndex <= n; ++caseIndex) {
        setTestCase(caseIndex);

        int r = inf.readInt(4, 20, "r");
        inf.readSpace();
        int c = inf.readInt(4, 20, "c");
        inf.readEoln();

        totalCells += r * c;
        ensuref(totalCells <= 10000000,
                "total maze cells must not exceed 10000000");

        vector<string> maze;
        pair<int, int> start = {-1, -1};
        pair<int, int> finish = {-1, -1};
        int startCount = 0;
        int finishCount = 0;

        for (int row = 0; row < r; ++row) {
            string line = inf.readLine("[XSF\\ ]{4,20}", "maze_row");
            ensuref(static_cast<int>(line.size()) == c,
                    "maze row %d has length %d, expected %d", row + 1,
                    static_cast<int>(line.size()), c);

            for (int col = 0; col < c; ++col) {
                char ch = line[col];
                if (ch == 'S') {
                    ++startCount;
                    start = {row, col};
                } else if (ch == 'F') {
                    ++finishCount;
                    finish = {row, col};
                }
            }
            maze.push_back(line);
        }

        ensuref(startCount == 1, "maze must contain exactly one S, found %d",
                startCount);
        ensuref(finishCount == 1, "maze must contain exactly one F, found %d",
                finishCount);
        ensuref(start != finish, "start and finish must be different cells");

        for (int col = 0; col < c; ++col) {
            ensuref(maze[0][col] == 'X',
                    "top border must be all walls, column %d", col + 1);
            ensuref(maze[r - 1][col] == 'X',
                    "bottom border must be all walls, column %d", col + 1);
        }
        for (int row = 0; row < r; ++row) {
            ensuref(maze[row][0] == 'X',
                    "left border must be all walls, row %d", row + 1);
            ensuref(maze[row][c - 1] == 'X',
                    "right border must be all walls, row %d", row + 1);
        }

        ensuref(hasNoLeftTurnPath(maze, start, finish),
                "no no-left-turn path from S to F");
    }

    inf.readEof();
}
