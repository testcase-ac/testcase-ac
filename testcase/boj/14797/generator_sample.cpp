#include "testlib.h"

#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using namespace std;

struct CaseData {
    int rows;
    int cols;
    vector<string> grid;
};

static vector<pair<int, int>> validShapes() {
    vector<pair<int, int>> shapes;
    for (int r = 1; r <= 12; ++r) {
        for (int c = 1; c <= 12; ++c) {
            if (r * c <= 12) {
                shapes.push_back({r, c});
            }
        }
    }
    return shapes;
}

static CaseData makeCase(int mode, const vector<pair<int, int>>& shapes) {
    auto [rows, cols] = rnd.any(shapes);
    int cells = rows * cols;

    if (mode == 1) {
        if (rnd.next(2) == 0) {
            rows = 1;
            cols = rnd.next(1, 12);
        } else {
            rows = rnd.next(1, 12);
            cols = 1;
        }
        cells = rows * cols;
    } else if (mode == 2) {
        vector<pair<int, int>> maxShapes;
        for (auto shape : shapes) {
            if (shape.first * shape.second == 12) {
                maxShapes.push_back(shape);
            }
        }
        tie(rows, cols) = rnd.any(maxShapes);
        cells = rows * cols;
    }

    vector<string> grid(rows, string(cols, '?'));
    vector<pair<int, int>> positions;
    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < cols; ++c) {
            positions.push_back({r, c});
        }
    }
    shuffle(positions.begin(), positions.end());

    int letterCount = 1;
    if (mode == 0) {
        letterCount = 1;
    } else if (mode == 3) {
        letterCount = min(cells, rnd.next(max(1, cells - 2), cells));
    } else if (mode == 4) {
        letterCount = cells == 1 ? 1 : rnd.next(2, min(6, cells));
    } else {
        letterCount = rnd.next(1, min(cells, 6));
    }

    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    shuffle(letters.begin(), letters.end());
    for (int i = 0; i < letterCount; ++i) {
        auto [r, c] = positions[i];
        grid[r][c] = letters[i];
    }

    return {rows, cols, grid};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const vector<pair<int, int>> shapes = validShapes();
    int testCount = rnd.next(12, 40);
    println(testCount);

    for (int tc = 0; tc < testCount; ++tc) {
        CaseData data = makeCase(tc % 5, shapes);
        println(data.rows, data.cols);
        for (const string& row : data.grid) {
            println(row);
        }
    }

    return 0;
}
