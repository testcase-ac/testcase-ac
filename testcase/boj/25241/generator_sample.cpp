#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<pair<int, int>> shapes;
    for (int r = 1; r <= 200; ++r) {
        for (int c = 1; c <= 200; ++c) {
            int cells = r * c;
            if (3 <= cells && cells <= 200) {
                shapes.push_back({r, c});
            }
        }
    }

    int mode = rnd.next(0, 5);
    int r, c;
    if (mode == 0) {
        r = 1;
        c = rnd.next(3, 30);
    } else if (mode == 1) {
        r = rnd.next(3, 30);
        c = 1;
    } else if (mode == 2) {
        r = rnd.next(2, 8);
        c = rnd.next((3 + r - 1) / r, min(25, 200 / r));
    } else if (mode == 3) {
        r = rnd.next(1, 10);
        c = rnd.next(max(3, 160 / r), 200 / r);
    } else {
        tie(r, c) = rnd.any(shapes);
    }

    int cells = r * c;
    int nMode = rnd.next(0, 3);
    int n;
    if (nMode == 0) {
        n = 3;
    } else if (nMode == 1) {
        n = cells;
    } else if (nMode == 2) {
        n = rnd.next(3, min(cells, 12));
    } else {
        n = rnd.next(3, cells);
    }

    vector<int> ids(n);
    for (int i = 0; i < n; ++i) {
        ids[i] = i + 1;
    }
    shuffle(ids.begin(), ids.end());
    vector<int> special = {ids[0], ids[1], ids[2]};

    int bonusMode = rnd.next(0, 3);
    vector<int> bonus(3);
    if (bonusMode == 0) {
        int base = rnd.next(1, 20);
        for (int i = 0; i < 3; ++i) {
            bonus[i] = base + rnd.next(0, 5);
        }
    } else if (bonusMode == 1) {
        for (int i = 0; i < 3; ++i) {
            bonus[i] = rnd.next(9000, 10000);
        }
    } else {
        for (int i = 0; i < 3; ++i) {
            bonus[i] = rnd.next(1, 10000);
        }
    }

    vector<vector<int>> value(r, vector<int>(c));
    int valueMode = rnd.next(0, 4);
    for (int i = 0; i < r; ++i) {
        for (int j = 0; j < c; ++j) {
            if (valueMode == 0) {
                value[i][j] = rnd.next(1, 30);
            } else if (valueMode == 1) {
                value[i][j] = rnd.next(9900, 10000);
            } else if (valueMode == 2) {
                value[i][j] = (i + j) % 2 == 0 ? rnd.next(1, 20) : rnd.next(9000, 10000);
            } else if (valueMode == 3) {
                value[i][j] = 1 + i * c + j;
            } else {
                value[i][j] = rnd.next(1, 10000);
            }
        }
    }

    println(r, c, n);
    println(special);
    println(bonus);
    for (int i = 0; i < r; ++i) {
        println(value[i]);
    }

    return 0;
}
