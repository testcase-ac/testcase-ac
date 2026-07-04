#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>
using namespace std;

using Point = pair<int, int>;

const int DR[4] = {-1, 0, 1, 0};
const int DC[4] = {0, 1, 0, -1};

bool inside(int r, int c, int rows, int cols) {
    return 0 <= r && r < rows && 0 <= c && c < cols;
}

vector<Point> buildTurtle(int rows, int cols, int targetSize) {
    set<Point> cells;
    cells.insert({rnd.next(rows), rnd.next(cols)});

    for (int attempt = 0; (int)cells.size() < targetSize && attempt < targetSize * 80; ++attempt) {
        Point base = rnd.any(vector<Point>(cells.begin(), cells.end()));
        int dir = rnd.next(4);
        int nr = base.first + DR[dir];
        int nc = base.second + DC[dir];
        if (inside(nr, nc, rows, cols)) {
            cells.insert({nr, nc});
        }
    }

    return vector<Point>(cells.begin(), cells.end());
}

vector<Point> buildRectangleTurtle(int rows, int cols) {
    int h = rnd.next(1, min(4, rows));
    int w = rnd.next(1, min(4, cols));
    int top = rnd.next(0, rows - h);
    int left = rnd.next(0, cols - w);

    vector<Point> cells;
    for (int r = top; r < top + h; ++r) {
        for (int c = left; c < left + w; ++c) {
            cells.push_back({r, c});
        }
    }
    return cells;
}

Point randomEmptyCell(const vector<string>& grid) {
    vector<Point> empty;
    for (int r = 0; r < (int)grid.size(); ++r) {
        for (int c = 0; c < (int)grid[r].size(); ++c) {
            if (grid[r][c] == '.') {
                empty.push_back({r, c});
            }
        }
    }
    return rnd.any(empty);
}

void addRandomObstacles(vector<string>& grid, int count) {
    for (int placed = 0; placed < count; ++placed) {
        vector<Point> empty;
        for (int r = 0; r < (int)grid.size(); ++r) {
            for (int c = 0; c < (int)grid[r].size(); ++c) {
                if (grid[r][c] == '.') {
                    empty.push_back({r, c});
                }
            }
        }
        if (empty.empty()) {
            return;
        }
        Point cell = rnd.any(empty);
        grid[cell.first][cell.second] = '#';
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int rows = rnd.next(2, 12);
    int cols = rnd.next(2, 12);
    if (mode == 1) {
        rows = rnd.any(vector<int>{2, 3, 4, 10});
        cols = rnd.next(2, 12);
    } else if (mode == 2) {
        rows = rnd.next(6, 18);
        cols = rnd.next(6, 18);
    } else if (mode == 3) {
        rows = rnd.next(10, 25);
        cols = rnd.next(10, 25);
    } else if (mode == 4) {
        rows = rnd.next(2, 5);
        cols = rnd.next(2, 5);
    }

    vector<Point> turtle;
    if (mode == 2) {
        turtle = buildRectangleTurtle(rows, cols);
    } else {
        int maxSize = min(rows * cols - 1, mode == 3 ? 30 : 12);
        int targetSize = rnd.next(1, maxSize);
        turtle = buildTurtle(rows, cols, targetSize);
    }

    vector<string> grid(rows, string(cols, '.'));
    for (Point cell : turtle) {
        grid[cell.first][cell.second] = 'T';
    }

    Point home = randomEmptyCell(grid);
    if (mode == 1) {
        vector<Point> nearTurtle;
        for (Point cell : turtle) {
            for (int dir = 0; dir < 4; ++dir) {
                int nr = cell.first + DR[dir];
                int nc = cell.second + DC[dir];
                if (inside(nr, nc, rows, cols) && grid[nr][nc] == '.') {
                    nearTurtle.push_back({nr, nc});
                }
            }
        }
        if (!nearTurtle.empty()) {
            home = rnd.any(nearTurtle);
        }
    }
    grid[home.first][home.second] = 'H';

    int obstacleLimit = min(20, rows * cols - (int)turtle.size() - 1);
    int obstacleCount = 0;
    if (mode == 0) {
        obstacleCount = rnd.next(0, min(3, obstacleLimit));
    } else if (mode == 2) {
        obstacleCount = rnd.next(0, min(10, obstacleLimit));
    } else if (mode == 3) {
        obstacleCount = rnd.next(min(10, obstacleLimit), obstacleLimit);
    } else if (mode == 4) {
        obstacleCount = rnd.next(0, obstacleLimit);
    }
    addRandomObstacles(grid, obstacleCount);

    println(rows, cols);
    for (const string& row : grid) {
        println(row);
    }
}
