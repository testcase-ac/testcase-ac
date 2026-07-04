#include "testlib.h"
#include <algorithm>
#include <utility>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int N;
    if (mode == 0) {
        N = rnd.next(2, 4);
    } else if (mode == 1) {
        N = rnd.next(5, 8);
    } else if (mode == 2) {
        N = rnd.next(6, 12);
    } else if (mode == 3) {
        N = rnd.next(8, 15);
    } else {
        N = rnd.next(2, 15);
    }

    int maxHouses = min(2 * N, N * N - 1);
    int houseCount;
    if (mode == 0) {
        houseCount = rnd.next(1, min(maxHouses, 3));
    } else if (mode == 3) {
        houseCount = rnd.next(max(1, 2 * N - 3), 2 * N);
    } else {
        houseCount = rnd.next(1, maxHouses);
    }

    int maxChicken = min(13, N * N - houseCount);
    int chickenCount;
    if (mode == 0) {
        chickenCount = rnd.next(1, min(maxChicken, 3));
    } else if (mode == 3) {
        chickenCount = rnd.next(max(1, maxChicken - 3), maxChicken);
    } else {
        chickenCount = rnd.next(1, maxChicken);
    }
    int M = rnd.next(1, chickenCount);

    vector<pair<int, int>> cells;
    for (int r = 0; r < N; ++r) {
        for (int c = 0; c < N; ++c) {
            cells.push_back({r, c});
        }
    }

    if (mode == 1) {
        sort(cells.begin(), cells.end(), [](const auto& a, const auto& b) {
            return a.first + a.second < b.first + b.second;
        });
        int span = min<int>(cells.size(), max(4, 2 * (houseCount + chickenCount)));
        shuffle(cells.begin(), cells.begin() + span);
    } else if (mode == 2) {
        sort(cells.begin(), cells.end(), [N](const auto& a, const auto& b) {
            int da = min({a.first, a.second, N - 1 - a.first, N - 1 - a.second});
            int db = min({b.first, b.second, N - 1 - b.first, N - 1 - b.second});
            return da < db;
        });
        int span = min<int>(cells.size(), max(4, 2 * (houseCount + chickenCount)));
        shuffle(cells.begin(), cells.begin() + span);
    } else {
        shuffle(cells.begin(), cells.end());
    }

    vector<vector<int>> grid(N, vector<int>(N, 0));
    int index = 0;
    for (int i = 0; i < houseCount; ++i) {
        auto [r, c] = cells[index++];
        grid[r][c] = 1;
    }
    for (int i = 0; i < chickenCount; ++i) {
        auto [r, c] = cells[index++];
        grid[r][c] = 2;
    }

    println(N, M);
    for (const auto& row : grid) {
        println(row);
    }

    return 0;
}
