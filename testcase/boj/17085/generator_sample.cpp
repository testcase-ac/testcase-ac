#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(2, 15);
    int m = rnd.next(2, 15);
    vector<string> board(n, string(m, '.'));

    auto setFilled = [&](int r, int c) {
        if (0 <= r && r < n && 0 <= c && c < m) {
            board[r][c] = '#';
        }
    };

    if (mode == 0) {
        double density = rnd.next(0.10, 0.35);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (rnd.next() < density) {
                    board[r][c] = '#';
                }
            }
        }
    } else if (mode == 1) {
        double density = rnd.next(0.55, 0.95);
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                if (rnd.next() < density) {
                    board[r][c] = '#';
                }
            }
        }
    } else if (mode == 2) {
        for (int r = 0; r < n; ++r) {
            if (rnd.next(0, 1)) {
                for (int c = 0; c < m; ++c) {
                    board[r][c] = '#';
                }
            }
        }
        for (int c = 0; c < m; ++c) {
            if (rnd.next(0, 1)) {
                for (int r = 0; r < n; ++r) {
                    board[r][c] = '#';
                }
            }
        }
    } else if (mode == 3) {
        int count = rnd.next(2, min(n * m, 12));
        vector<pair<int, int>> cells;
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                cells.push_back({r, c});
            }
        }
        shuffle(cells.begin(), cells.end());
        for (int i = 0; i < count; ++i) {
            board[cells[i].first][cells[i].second] = '#';
        }
    } else if (mode == 4) {
        int arms = rnd.next(1, 3);
        int centers = rnd.next(1, 3);
        for (int i = 0; i < centers; ++i) {
            int r = rnd.next(0, n - 1);
            int c = rnd.next(0, m - 1);
            setFilled(r, c);
            for (int d = 1; d <= arms; ++d) {
                setFilled(r - d, c);
                setFilled(r + d, c);
                setFilled(r, c - d);
                setFilled(r, c + d);
            }
        }
    } else {
        for (int r = 0; r < n; ++r) {
            for (int c = 0; c < m; ++c) {
                bool nearBorder = r == 0 || c == 0 || r + 1 == n || c + 1 == m;
                if (nearBorder || rnd.next() < 0.25) {
                    board[r][c] = '#';
                }
            }
        }
    }

    vector<pair<int, int>> emptyCells;
    int filled = 0;
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < m; ++c) {
            if (board[r][c] == '#') {
                ++filled;
            } else {
                emptyCells.push_back({r, c});
            }
        }
    }

    shuffle(emptyCells.begin(), emptyCells.end());
    while (filled < 2 && !emptyCells.empty()) {
        auto [r, c] = emptyCells.back();
        emptyCells.pop_back();
        board[r][c] = '#';
        ++filled;
    }

    println(n, m);
    for (const string& row : board) {
        println(row);
    }

    return 0;
}
