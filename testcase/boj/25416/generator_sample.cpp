#include "testlib.h"

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

const int N = 5;
const int DR[4] = {1, -1, 0, 0};
const int DC[4] = {0, 0, 1, -1};

bool inside(int r, int c) {
    return 0 <= r && r < N && 0 <= c && c < N;
}

vector<pair<int, int>> allCells() {
    vector<pair<int, int>> cells;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            cells.push_back({r, c});
        }
    }
    return cells;
}

bool reachable(const vector<vector<int>>& board, pair<int, int> start, pair<int, int> target) {
    vector<vector<int>> seen(N, vector<int>(N));
    queue<pair<int, int>> q;
    q.push(start);
    seen[start.first][start.second] = 1;

    while (!q.empty()) {
        auto [r, c] = q.front();
        q.pop();
        if (make_pair(r, c) == target) {
            return true;
        }
        for (int d = 0; d < 4; ++d) {
            int nr = r + DR[d];
            int nc = c + DC[d];
            if (inside(nr, nc) && !seen[nr][nc] && board[nr][nc] != -1) {
                seen[nr][nc] = 1;
                q.push({nr, nc});
            }
        }
    }
    return false;
}

pair<int, int> randomCellExcept(pair<int, int> banned) {
    vector<pair<int, int>> cells = allCells();
    cells.erase(remove(cells.begin(), cells.end(), banned), cells.end());
    return rnd.any(cells);
}

void printCase(const vector<vector<int>>& board, pair<int, int> start) {
    for (int r = 0; r < N; ++r) {
        println(board[r]);
    }
    println(start.first, start.second);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    vector<vector<int>> board(N, vector<int>(N, 0));
    pair<int, int> target = rnd.any(allCells());
    pair<int, int> start = randomCellExcept(target);

    if (mode == 0) {
        int walls = rnd.next(0, 7);
        vector<pair<int, int>> cells = allCells();
        shuffle(cells.begin(), cells.end());
        for (auto cell : cells) {
            if (walls == 0) {
                break;
            }
            if (cell != target && cell != start) {
                board[cell.first][cell.second] = -1;
                --walls;
            }
        }
    } else if (mode == 1) {
        vector<pair<int, int>> neighbors;
        for (int d = 0; d < 4; ++d) {
            int nr = target.first + DR[d];
            int nc = target.second + DC[d];
            if (inside(nr, nc)) {
                neighbors.push_back({nr, nc});
            }
        }
        start = rnd.any(neighbors);
        for (auto cell : allCells()) {
            if (cell != target && cell != start && rnd.next(100) < 35) {
                board[cell.first][cell.second] = -1;
            }
        }
    } else if (mode == 2) {
        int wallCol = rnd.next(1, 3);
        int gap = rnd.next(N);
        for (int r = 0; r < N; ++r) {
            if (r != gap) {
                board[r][wallCol] = -1;
            }
        }
        target = {rnd.next(N), rnd.next(wallCol + 1, N - 1)};
        start = {rnd.next(N), rnd.next(0, wallCol - 1)};
    } else if (mode == 3) {
        target = rnd.any(allCells());
        board.assign(N, vector<int>(N, -1));
        vector<pair<int, int>> path;
        start = randomCellExcept(target);
        pair<int, int> cur = start;
        path.push_back(cur);
        while (cur.first != target.first) {
            cur.first += (cur.first < target.first ? 1 : -1);
            path.push_back(cur);
        }
        while (cur.second != target.second) {
            cur.second += (cur.second < target.second ? 1 : -1);
            path.push_back(cur);
        }
        for (auto cell : path) {
            board[cell.first][cell.second] = 0;
        }
        int extraOpen = rnd.next(0, 6);
        vector<pair<int, int>> cells = allCells();
        shuffle(cells.begin(), cells.end());
        for (auto cell : cells) {
            if (extraOpen == 0) {
                break;
            }
            if (board[cell.first][cell.second] == -1 && cell != target) {
                board[cell.first][cell.second] = 0;
                --extraOpen;
            }
        }
    } else {
        target = rnd.any(allCells());
        board.assign(N, vector<int>(N, 0));
        for (int d = 0; d < 4; ++d) {
            int nr = target.first + DR[d];
            int nc = target.second + DC[d];
            if (inside(nr, nc)) {
                board[nr][nc] = -1;
            }
        }
        vector<pair<int, int>> candidates;
        for (auto cell : allCells()) {
            if (cell != target && board[cell.first][cell.second] == 0) {
                candidates.push_back(cell);
            }
        }
        start = rnd.any(candidates);
        int extraWalls = rnd.next(0, 5);
        vector<pair<int, int>> cells = candidates;
        shuffle(cells.begin(), cells.end());
        for (auto cell : cells) {
            if (extraWalls == 0) {
                break;
            }
            if (cell != start) {
                board[cell.first][cell.second] = -1;
                --extraWalls;
            }
        }
    }

    board[target.first][target.second] = 1;
    board[start.first][start.second] = 0;

    if (mode != 4 && !reachable(board, start, target)) {
        for (auto cell : allCells()) {
            if (cell != target && cell != start) {
                board[cell.first][cell.second] = 0;
            }
        }
    }

    printCase(board, start);
    return 0;
}
