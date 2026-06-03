#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

const int N = 10;

void flip(vector<string>& grid, int r, int c) {
    if (r < 0 || r >= N || c < 0 || c >= N) return;
    grid[r][c] = grid[r][c] == 'O' ? '#' : 'O';
}

void press(vector<string>& grid, int r, int c) {
    flip(grid, r, c);
    flip(grid, r - 1, c);
    flip(grid, r + 1, c);
    flip(grid, r, c - 1);
    flip(grid, r, c + 1);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    vector<string> grid(N, string(N, '#'));

    if (mode == 0) {
        int onWeight = rnd.next(1, 9);
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if (rnd.next(1, 10) <= onWeight) grid[r][c] = 'O';
            }
        }
    } else if (mode == 1) {
        int presses = rnd.next(1, 25);
        for (int i = 0; i < presses; ++i) {
            press(grid, rnd.next(0, N - 1), rnd.next(0, N - 1));
        }
    } else if (mode == 2) {
        int period = rnd.next(2, 5);
        int phase = rnd.next(0, period - 1);
        for (int r = 0; r < N; ++r) {
            for (int c = 0; c < N; ++c) {
                if ((r + c + phase) % period == 0) grid[r][c] = 'O';
            }
        }
    } else if (mode == 3) {
        bool horizontal = rnd.next(0, 1);
        int stripeCount = rnd.next(1, 5);
        vector<int> order(N);
        for (int i = 0; i < N; ++i) order[i] = i;
        shuffle(order.begin(), order.end());

        for (int i = 0; i < stripeCount; ++i) {
            int line = order[i];
            for (int j = 0; j < N; ++j) {
                if (horizontal) grid[line][j] = 'O';
                else grid[j][line] = 'O';
            }
        }
    } else if (mode == 4) {
        int extra = rnd.next(0, 12);
        vector<pair<int, int>> cells;
        for (int i = 0; i < N; ++i) {
            cells.push_back({0, i});
            cells.push_back({N - 1, i});
            cells.push_back({i, 0});
            cells.push_back({i, N - 1});
        }
        shuffle(cells.begin(), cells.end());

        int take = rnd.next(1, 16);
        for (int i = 0; i < take; ++i) grid[cells[i].first][cells[i].second] = 'O';
        for (int i = 0; i < extra; ++i) grid[rnd.next(0, N - 1)][rnd.next(0, N - 1)] = 'O';
    } else {
        char fill = rnd.next(0, 1) ? 'O' : '#';
        for (int r = 0; r < N; ++r) grid[r] = string(N, fill);

        int holes = rnd.next(0, 20);
        for (int i = 0; i < holes; ++i) {
            int r = rnd.next(0, N - 1);
            int c = rnd.next(0, N - 1);
            grid[r][c] = grid[r][c] == 'O' ? '#' : 'O';
        }
    }

    for (const string& row : grid) println(row);
    return 0;
}
