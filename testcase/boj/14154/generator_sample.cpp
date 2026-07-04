#include "testlib.h"

#include <algorithm>
#include <array>
#include <cctype>
#include <string>
#include <utility>
#include <vector>

using namespace std;

const array<int, 4> dr = {-1, 0, 1, 0};
const array<int, 4> dc = {0, 1, 0, -1};

bool inside(int n, int r, int c) {
    return 0 <= r && r < n && 0 <= c && c < n;
}

bool touchesCurrentPath(const vector<pair<int, int>>& path, int r, int c) {
    for (int i = 0; i < int(path.size()); ++i) {
        if (path[i].first == r && path[i].second == c) {
            return true;
        }
    }

    for (int i = 0; i + 1 < int(path.size()); ++i) {
        if (abs(path[i].first - r) + abs(path[i].second - c) == 1) {
            return true;
        }
    }
    return false;
}

bool addSnake(vector<string>& board, int id, int targetLength) {
    int n = int(board.size());

    for (int attempt = 0; attempt < 250; ++attempt) {
        vector<pair<int, int>> path;
        int r = rnd.next(n);
        int c = rnd.next(n);
        if (board[r][c] != '.') {
            continue;
        }
        path.push_back({r, c});

        while (int(path.size()) < targetLength) {
            vector<int> dirs = {0, 1, 2, 3};
            shuffle(dirs.begin(), dirs.end());

            bool advanced = false;
            for (int dir : dirs) {
                int nr = path.back().first + dr[dir];
                int nc = path.back().second + dc[dir];
                if (!inside(n, nr, nc) || board[nr][nc] != '.') {
                    continue;
                }
                if (touchesCurrentPath(path, nr, nc)) {
                    continue;
                }

                path.push_back({nr, nc});
                advanced = true;
                break;
            }

            if (!advanced) {
                break;
            }
        }

        if (int(path.size()) != targetLength) {
            continue;
        }

        if (rnd.next(2) == 1) {
            reverse(path.begin(), path.end());
        }

        char head = char('A' + id);
        char body = char('a' + id);
        board[path[0].first][path[0].second] = head;
        for (int i = 1; i < int(path.size()); ++i) {
            board[path[i].first][path[i].second] = body;
        }
        return true;
    }

    return false;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    int sizeMode = rnd.next(100);
    if (sizeMode < 15) {
        n = rnd.next(2, 4);
    } else if (sizeMode < 80) {
        n = rnd.next(5, 12);
    } else {
        n = rnd.next(13, 22);
    }

    int t;
    int timeMode = rnd.next(100);
    if (timeMode < 55) {
        t = rnd.next(1, 30);
    } else if (timeMode < 85) {
        t = rnd.next(31, 2000);
    } else {
        t = rnd.next(2001, 1000000);
    }

    vector<string> board(n, string(n, '.'));
    int maxSnakes = min(26, max(1, n * n / 10));
    int snakeCount = rnd.next(1, maxSnakes);

    int placed = 0;
    for (int id = 0; id < snakeCount; ++id) {
        int maxLength = max(2, min(10, n * n / max(2, snakeCount + 1)));
        int length = rnd.next(2, maxLength);
        if (addSnake(board, id, length)) {
            ++placed;
        }
    }

    while (placed == 0) {
        board.assign(n, string(n, '.'));
        placed += addSnake(board, 0, 2);
    }

    double obstacleProb = rnd.next(0.0, 0.22);
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (board[r][c] == '.' && rnd.next() < obstacleProb) {
                board[r][c] = '#';
            }
        }
    }

    println(n, t);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
