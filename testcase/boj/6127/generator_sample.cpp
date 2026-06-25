#include "testlib.h"

#include <algorithm>
#include <utility>
#include <vector>

using namespace std;

int clampCell(int value, int n) {
    return max(1, min(n, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = (mode == 5 ? rnd.next(80, 100) : rnd.next(1, 18));
    vector<pair<int, int>> cows;

    if (mode == 0) {
        int k = rnd.next(1, min(12, n * n));
        for (int i = 0; i < k; ++i) {
            cows.push_back({rnd.next(1, n), rnd.next(1, n)});
        }
    } else if (mode == 1) {
        int row = rnd.next(1, n);
        int k = rnd.next(1, min(18, n + 6));
        for (int i = 0; i < k; ++i) {
            cows.push_back({row, rnd.next(1, n)});
        }
    } else if (mode == 2) {
        int col = rnd.next(1, n);
        int k = rnd.next(1, min(18, n + 6));
        for (int i = 0; i < k; ++i) {
            cows.push_back({rnd.next(1, n), col});
        }
    } else if (mode == 3) {
        int baseRow = rnd.next(1, n);
        int baseCol = rnd.next(1, n);
        int k = rnd.next(1, min(16, 2 * n));
        for (int i = 0; i < k; ++i) {
            int delta = rnd.next(-(n - 1), n - 1);
            if (rnd.next(0, 1) == 0) {
                cows.push_back({clampCell(baseRow + delta, n), clampCell(baseCol + delta, n)});
            } else {
                cows.push_back({clampCell(baseRow + delta, n), clampCell(baseCol - delta, n)});
            }
        }
    } else if (mode == 4) {
        int anchorRow = rnd.next(1, n);
        int anchorCol = rnd.next(1, n);
        int k = rnd.next(4, 20);
        for (int i = 0; i < k; ++i) {
            int direction = rnd.next(0, 7);
            int step = rnd.next(0, max(0, n - 1));
            int dr[8] = {-1, 1, 0, 0, -1, -1, 1, 1};
            int dc[8] = {0, 0, -1, 1, -1, 1, -1, 1};
            cows.push_back({clampCell(anchorRow + dr[direction] * step, n),
                            clampCell(anchorCol + dc[direction] * step, n)});
        }
    } else {
        int k = rnd.next(20, 60);
        vector<pair<int, int>> pool = {
            {1, 1},
            {1, n},
            {n, 1},
            {n, n},
            {(n + 1) / 2, (n + 1) / 2},
            {n / 2, n / 2 + 1},
        };
        for (int i = 0; i < k; ++i) {
            cows.push_back(rnd.any(pool));
        }
    }

    shuffle(cows.begin(), cows.end());

    println(n, static_cast<int>(cows.size()));
    for (auto cow : cows) {
        println(cow.first, cow.second);
    }

    return 0;
}
