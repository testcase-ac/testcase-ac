#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 3);
    int n = rnd.next(4, 12);
    int m = rnd.next(4, 12);
    vector<string> board(n, string(m, '#'));
    vector<pair<int, int>> cells;

    auto add_cell = [&](int r, int c) {
        if (r <= 0 || r >= n - 1 || c <= 0 || c >= m - 1) {
            return;
        }
        if (board[r][c] == '#') {
            board[r][c] = '.';
            cells.push_back({r, c});
        }
    };

    auto is_connected = [&]() {
        vector<vector<int>> seen(n, vector<int>(m, 0));
        vector<pair<int, int>> stack;
        for (int r = 1; r <= n - 2 && stack.empty(); ++r) {
            for (int c = 1; c <= m - 2; ++c) {
                if (board[r][c] != '#') {
                    stack.push_back({r, c});
                    seen[r][c] = 1;
                    break;
                }
            }
        }

        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};
        int reached = 0;
        while (!stack.empty()) {
            auto [r, c] = stack.back();
            stack.pop_back();
            ++reached;
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (board[nr][nc] == '#' || seen[nr][nc]) {
                    continue;
                }
                seen[nr][nc] = 1;
                stack.push_back({nr, nc});
            }
        }

        return reached == (int)cells.size();
    };

    if (mode == 0) {
        int top = rnd.next(1, n - 2);
        int bottom = rnd.next(top, n - 2);
        int left = rnd.next(1, m - 2);
        int right = rnd.next(left, m - 2);
        for (int r = top; r <= bottom; ++r) {
            for (int c = left; c <= right; ++c) {
                add_cell(r, c);
            }
        }
    } else if (mode == 1) {
        int r = rnd.next(1, n - 2);
        int c = rnd.next(1, m - 2);
        add_cell(r, c);

        int target = rnd.next(2, min((n - 2) * (m - 2), 30));
        const int dr[4] = {-1, 1, 0, 0};
        const int dc[4] = {0, 0, -1, 1};
        while ((int)cells.size() < target) {
            auto cur = rnd.any(cells);
            int dir = rnd.next(0, 3);
            add_cell(cur.first + dr[dir], cur.second + dc[dir]);
        }
    } else if (mode == 2) {
        bool horizontal = rnd.next(0, 1);
        if (horizontal) {
            int r = rnd.next(1, n - 2);
            for (int c = 1; c <= m - 2; ++c) {
                add_cell(r, c);
                if (rnd.next(0, 2) == 0) {
                    int target = rnd.next(1, n - 2);
                    for (int rr = min(r, target); rr <= max(r, target); ++rr) {
                        add_cell(rr, c);
                    }
                }
            }
        } else {
            int c = rnd.next(1, m - 2);
            for (int r = 1; r <= n - 2; ++r) {
                add_cell(r, c);
                if (rnd.next(0, 2) == 0) {
                    int target = rnd.next(1, m - 2);
                    for (int cc = min(c, target); cc <= max(c, target); ++cc) {
                        add_cell(r, cc);
                    }
                }
            }
        }
    } else {
        for (int r = 1; r <= n - 2; ++r) {
            for (int c = 1; c <= m - 2; ++c) {
                add_cell(r, c);
            }
        }

        vector<pair<int, int>> candidates = cells;
        shuffle(candidates.begin(), candidates.end());
        for (auto [r, c] : candidates) {
            if ((int)cells.size() <= 2 || rnd.next(0, 2) != 0) {
                continue;
            }
            int neighbors = 0;
            const int dr[4] = {-1, 1, 0, 0};
            const int dc[4] = {0, 0, -1, 1};
            for (int dir = 0; dir < 4; ++dir) {
                int nr = r + dr[dir];
                int nc = c + dc[dir];
                if (board[nr][nc] != '#') {
                    ++neighbors;
                }
            }
            if (neighbors <= 1) {
                continue;
            }
            board[r][c] = '#';
            cells.erase(find(cells.begin(), cells.end(), make_pair(r, c)));
            if (!is_connected()) {
                board[r][c] = '.';
                cells.push_back({r, c});
            }
        }
    }

    if ((int)cells.size() == 1) {
        auto [r, c] = cells[0];
        if (c + 1 <= m - 2) {
            add_cell(r, c + 1);
        } else {
            add_cell(r, c - 1);
        }
    }

    shuffle(cells.begin(), cells.end());
    board[cells[0].first][cells[0].second] = 'D';
    board[cells[1].first][cells[1].second] = 'R';

    println(n, m);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
