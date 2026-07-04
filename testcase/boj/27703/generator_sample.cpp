#include "testlib.h"

#include <utility>
#include <vector>

using namespace std;

struct TestCase {
    int rows;
    int cols;
    int redRow;
    int redCol;
    int blueRow;
    int blueCol;
};

static pair<int, int> randomCell(int rows, int cols) {
    return {rnd.next(1, rows), rnd.next(1, cols)};
}

static TestCase makeCase(int mode) {
    int rows;
    int cols;
    pair<int, int> red;
    pair<int, int> blue;

    if (mode == 0) {
        rows = rnd.next(1, 6);
        cols = rnd.next(2, 8);
        red = randomCell(rows, cols);
        if (red.second < cols) {
            blue = {red.first, red.second + 1};
        } else {
            blue = {red.first, red.second - 1};
        }
    } else if (mode == 1) {
        rows = rnd.next(2, 8);
        cols = rnd.next(1, 6);
        red = randomCell(rows, cols);
        if (red.first < rows) {
            blue = {red.first + 1, red.second};
        } else {
            blue = {red.first - 1, red.second};
        }
    } else if (mode == 2) {
        rows = rnd.next(2, 12);
        cols = rnd.next(2, 12);
        vector<pair<int, int>> corners = {{1, 1}, {1, cols}, {rows, 1}, {rows, cols}};
        red = rnd.any(corners);
        do {
            blue = rnd.any(corners);
        } while (blue == red);
    } else if (mode == 3) {
        rows = rnd.next(2, 10);
        cols = rnd.next(2, 10);
        red = randomCell(rows, cols);
        do {
            blue = randomCell(rows, cols);
        } while (blue == red);
    } else {
        rows = rnd.next(10, 30);
        cols = rnd.next(10, 30);
        red = randomCell(rows, cols);
        do {
            blue = randomCell(rows, cols);
        } while (blue == red);
    }

    return {rows, cols, red.first, red.second, blue.first, blue.second};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(5, 9);
    println(testCount);

    for (int i = 0; i < testCount; ++i) {
        TestCase tc = makeCase(rnd.next(0, 4));

        printf("\n");
        println(tc.rows, tc.cols);
        println(tc.redRow, tc.redCol);
        println(tc.blueRow, tc.blueCol);
    }

    return 0;
}
