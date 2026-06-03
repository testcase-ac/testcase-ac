#include "testlib.h"

#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    if (mode == 1 || mode == 2) {
        n = rnd.next(3, 6);
    } else if (mode == 3) {
        n = rnd.next(5, 10);
    } else {
        n = rnd.next(3, 10);
    }

    vector<int> values(n * n);
    iota(values.begin(), values.end(), 1);
    vector<int> order;
    order.reserve(n * n);

    if (mode == 0) {
        for (int row = 0; row < n; ++row) {
            for (int col = 0; col < n; ++col) {
                order.push_back(row * n + col);
            }
        }
    } else if (mode == 1) {
        for (int row = 0; row < n; ++row) {
            if (row % 2 == 0) {
                for (int col = 0; col < n; ++col) order.push_back(row * n + col);
            } else {
                for (int col = n - 1; col >= 0; --col) order.push_back(row * n + col);
            }
        }
    } else if (mode == 2) {
        for (int sum = 0; sum <= 2 * (n - 1); ++sum) {
            vector<int> diagonal;
            for (int row = 0; row < n; ++row) {
                int col = sum - row;
                if (0 <= col && col < n) {
                    diagonal.push_back(row * n + col);
                }
            }
            if (sum % 2 == 1) {
                reverse(diagonal.begin(), diagonal.end());
            }
            order.insert(order.end(), diagonal.begin(), diagonal.end());
        }
    } else if (mode == 3) {
        vector<bool> used(n * n, false);
        int row = rnd.next(0, n - 1);
        int col = rnd.next(0, n - 1);
        const int dr[] = {-2, -2, -1, -1, 1, 1, 2, 2};
        const int dc[] = {-1, 1, -2, 2, -2, 2, -1, 1};

        while (true) {
            order.push_back(row * n + col);
            used[row * n + col] = true;

            vector<int> nextCells;
            for (int step = 0; step < 8; ++step) {
                int nextRow = row + dr[step];
                int nextCol = col + dc[step];
                if (0 <= nextRow && nextRow < n && 0 <= nextCol && nextCol < n &&
                    !used[nextRow * n + nextCol]) {
                    nextCells.push_back(nextRow * n + nextCol);
                }
            }
            if (nextCells.empty()) {
                break;
            }

            int next = rnd.any(nextCells);
            row = next / n;
            col = next % n;
        }

        vector<int> rest;
        for (int cell = 0; cell < n * n; ++cell) {
            if (!used[cell]) rest.push_back(cell);
        }
        shuffle(rest.begin(), rest.end());
        order.insert(order.end(), rest.begin(), rest.end());
    } else if (mode == 4) {
        for (int parity = 0; parity < 2; ++parity) {
            vector<int> cells;
            for (int row = 0; row < n; ++row) {
                for (int col = 0; col < n; ++col) {
                    if ((row + col) % 2 == parity) {
                        cells.push_back(row * n + col);
                    }
                }
            }
            shuffle(cells.begin(), cells.end());
            order.insert(order.end(), cells.begin(), cells.end());
        }
    } else {
        for (int cell = 0; cell < n * n; ++cell) {
            order.push_back(cell);
        }
        shuffle(order.begin(), order.end());
    }

    if (rnd.next(0, 2) == 0) {
        int rotations = rnd.next(0, n * n - 1);
        rotate(values.begin(), values.begin() + rotations, values.end());
    }
    if (rnd.next(0, 3) == 0) {
        reverse(values.begin(), values.end());
    }

    vector<vector<int>> board(n, vector<int>(n));
    for (int i = 0; i < n * n; ++i) {
        int cell = order[i];
        board[cell / n][cell % n] = values[i];
    }

    println(n);
    for (int row = 0; row < n; ++row) {
        println(board[row]);
    }

    return 0;
}
