#include "testlib.h"

#include <algorithm>
#include <set>
#include <utility>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int n = rnd.next(1, 18);
    int radius = rnd.next(1, 18);
    vector<pair<int, int>> lamps;
    set<pair<int, int>> used;

    auto addLamp = [&](int row, int col) {
        row = max(1, min(n, row));
        col = max(1, min(n, col));
        if (used.insert({row, col}).second) {
            lamps.push_back({row, col});
        }
    };

    if (mode == 0) {
        n = rnd.next(1, 4);
        radius = rnd.next(1, 6);
        addLamp(rnd.next(1, n), rnd.next(1, n));
    } else if (mode == 1) {
        n = rnd.next(4, 14);
        radius = rnd.next(1, 5);
        int count = rnd.next(2, min(20, n * n));
        while ((int)lamps.size() < count) {
            addLamp(rnd.next(1, n), rnd.next(1, n));
        }
    } else if (mode == 2) {
        n = rnd.next(5, 18);
        radius = rnd.next(1, 6);
        int row = rnd.next(1, n);
        int start = rnd.next(1, n);
        int step = rnd.next(1, max(1, min(n, 2 * radius)));
        int count = rnd.next(3, min(12, n));
        for (int i = 0; i < count; ++i) {
            addLamp(row, 1 + (start + i * step - 1) % n);
        }
    } else if (mode == 3) {
        n = rnd.next(5, 18);
        radius = rnd.next(1, 6);
        int col = rnd.next(1, n);
        int start = rnd.next(1, n);
        int step = rnd.next(1, max(1, min(n, 2 * radius)));
        int count = rnd.next(3, min(12, n));
        for (int i = 0; i < count; ++i) {
            addLamp(1 + (start + i * step - 1) % n, col);
        }
    } else if (mode == 4) {
        n = rnd.next(4, 10);
        radius = rnd.next(1, 4);
        int rows = rnd.next(2, min(5, n));
        int cols = rnd.next(2, min(5, n));
        int rowStart = rnd.next(1, n);
        int colStart = rnd.next(1, n);
        for (int i = 0; i < rows; ++i) {
            for (int j = 0; j < cols; ++j) {
                if (rnd.next(0, 99) < 75) {
                    addLamp(1 + (rowStart + i - 1) % n,
                            1 + (colStart + j - 1) % n);
                }
            }
        }
    } else {
        n = rnd.next(6, 18);
        radius = rnd.next(2, 8);
        int gap = max(1, min(n - 1, 2 * radius - 1 + rnd.next(-1, 1)));
        int row = rnd.next(1, n);
        int col = rnd.next(1, n);
        int c1 = rnd.next(1, n - gap);
        int r1 = rnd.next(1, n - gap);
        addLamp(row, c1);
        addLamp(row, c1 + gap);
        addLamp(r1, col);
        addLamp(r1 + gap, col);
        int extras = rnd.next(0, min(8, n * n - (int)lamps.size()));
        while (extras-- > 0) {
            addLamp(rnd.next(1, n), rnd.next(1, n));
        }
    }

    if (lamps.empty()) {
        addLamp(1, 1);
    }

    shuffle(lamps.begin(), lamps.end());
    println(n, radius, (int)lamps.size());
    for (auto lamp : lamps) {
        println(lamp.first, lamp.second);
    }

    return 0;
}
