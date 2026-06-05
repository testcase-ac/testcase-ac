#include "testlib.h"

#include <array>
#include <utility>
#include <vector>

using namespace std;

const int N = 5;

using Board = array<array<int, N>, N>;

vector<pair<int, int>> allCells() {
    vector<pair<int, int>> cells;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            cells.push_back({r, c});
        }
    }
    return cells;
}

void printCase(const Board& board, pair<int, int> start) {
    for (int r = 0; r < N; ++r) {
        vector<int> row;
        for (int c = 0; c < N; ++c) {
            row.push_back(board[r][c]);
        }
        println(row);
    }
    println(start.first, start.second);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    Board board{};
    auto cells = allCells();
    shuffle(cells.begin(), cells.end());

    pair<int, int> start = cells.back();
    cells.pop_back();
    board[start.first][start.second] = 0;

    int mode = rnd.next(0, 5);

    if (mode == 0) {
        int appleCount = rnd.next(0, 2);
        for (int i = 0; i < appleCount; ++i) {
            auto [r, c] = cells.back();
            cells.pop_back();
            board[r][c] = 1;
        }
        for (auto [r, c] : cells) {
            if (rnd.next(100) < 25) {
                board[r][c] = -1;
            }
        }
    } else if (mode == 1) {
        int appleCount = rnd.next(3, 8);
        int obstacleChance = rnd.next(0, 25);
        for (auto [r, c] : cells) {
            if (appleCount > 0 && rnd.next(100) < 35) {
                board[r][c] = 1;
                --appleCount;
            } else if (rnd.next(100) < obstacleChance) {
                board[r][c] = -1;
            }
        }
        while (appleCount > 0) {
            auto [r, c] = rnd.any(cells);
            if (board[r][c] == 0) {
                board[r][c] = 1;
                --appleCount;
            }
        }
    } else if (mode == 2) {
        int obstacleChance = rnd.next(45, 75);
        int appleCount = rnd.next(3, 6);
        for (auto [r, c] : cells) {
            if (rnd.next(100) < obstacleChance) {
                board[r][c] = -1;
            }
        }
        shuffle(cells.begin(), cells.end());
        for (auto [r, c] : cells) {
            if (appleCount == 0) {
                break;
            }
            board[r][c] = 1;
            --appleCount;
        }
    } else if (mode == 3) {
        vector<pair<int, int>> path;
        path.push_back(start);
        pair<int, int> cur = start;
        int targetLength = rnd.next(4, 10);
        while ((int)path.size() < targetLength) {
            vector<pair<int, int>> nexts;
            const int dr[4] = {1, -1, 0, 0};
            const int dc[4] = {0, 0, 1, -1};
            for (int d = 0; d < 4; ++d) {
                int nr = cur.first + dr[d];
                int nc = cur.second + dc[d];
                if (nr < 0 || nr >= N || nc < 0 || nc >= N) {
                    continue;
                }
                bool used = false;
                for (auto p : path) {
                    used |= p == make_pair(nr, nc);
                }
                if (!used) {
                    nexts.push_back({nr, nc});
                }
            }
            if (nexts.empty()) {
                break;
            }
            cur = rnd.any(nexts);
            path.push_back(cur);
        }

        for (auto [r, c] : cells) {
            board[r][c] = -1;
        }
        for (auto [r, c] : path) {
            board[r][c] = 0;
        }
        int applesOnPath = min(3, (int)path.size() - 1);
        vector<int> positions;
        for (int i = 1; i < (int)path.size(); ++i) {
            positions.push_back(i);
        }
        shuffle(positions.begin(), positions.end());
        for (int i = 0; i < applesOnPath; ++i) {
            auto [r, c] = path[positions[i]];
            board[r][c] = 1;
        }
    } else {
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                board[r][c] = rnd.next(100) < 12 ? -1 : 0;
            }
        }
        board[start.first][start.second] = 0;
        int appleCount = rnd.next(9, 18);
        shuffle(cells.begin(), cells.end());
        for (auto [r, c] : cells) {
            if (appleCount == 0) {
                break;
            }
            if (board[r][c] == 0) {
                board[r][c] = 1;
                --appleCount;
            }
        }
    }

    board[start.first][start.second] = 0;
    printCase(board, start);
    return 0;
}
