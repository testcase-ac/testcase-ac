#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

struct CaseData {
    int x;
    int y;
    vector<string> cells;
};

vector<string> makePattern(int mode, int emptyIndex) {
    const string colors = "BWR";
    vector<string> cells(9, "W");

    if (mode == 0) {
        fill(cells.begin(), cells.end(), string(1, rnd.any(colors)));
    } else if (mode == 1) {
        for (string& cell : cells) {
            cell = string(1, rnd.any(colors));
        }
    } else if (mode == 2) {
        vector<string> bag;
        for (char color : colors) {
            for (int i = 0; i < 3; ++i) {
                bag.push_back(string(1, color));
            }
        }
        shuffle(bag.begin(), bag.end());
        cells = bag;
    } else {
        for (int row = 0; row < 3; ++row) {
            for (int col = 0; col < 3; ++col) {
                int value = row * 2 + col + rnd.next(0, 2);
                cells[row * 3 + col] = string(1, colors[value % 3]);
            }
        }
    }

    cells[emptyIndex] = "E";
    return cells;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<CaseData> tests;
    int caseCount = rnd.next(4, 10);
    for (int i = 0; i < caseCount; ++i) {
        int x = rnd.next(1, 3);
        int y = rnd.next(1, 3);
        int emptyIndex;
        if (i == 0) {
            emptyIndex = (y - 1) * 3 + (x - 1);
        } else if (i == 1) {
            emptyIndex = rnd.next(9);
        } else {
            emptyIndex = rnd.wnext(9, i % 2 == 0 ? -2 : 2);
        }

        tests.push_back({x, y, makePattern(rnd.next(0, 3), emptyIndex)});
    }

    if (rnd.next(2) == 0) {
        tests.push_back({rnd.next(1, 3), rnd.next(1, 3), makePattern(0, rnd.next(9))});
    }

    for (const CaseData& test : tests) {
        println(test.x, test.y);
        for (int row = 0; row < 3; ++row) {
            println(test.cells[row * 3], test.cells[row * 3 + 1], test.cells[row * 3 + 2]);
        }
    }
    println(0, 0);

    return 0;
}
