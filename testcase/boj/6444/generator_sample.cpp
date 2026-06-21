#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

static string columnName(int column) {
    string name;
    while (column > 0) {
        --column;
        name.push_back(char('A' + column % 26));
        column /= 26;
    }
    reverse(name.begin(), name.end());
    return name;
}

static string cellName(int index, int columns) {
    int row = index / columns + 1;
    int column = index % columns + 1;
    return columnName(column) + toString(row);
}

static string makeFormula(int cell, int columns, int refs) {
    string formula = "=";
    for (int i = 0; i < refs; ++i) {
        if (i > 0) formula += "+";
        formula += cellName(rnd.next(0, cell - 1), columns);
    }
    return formula;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = rnd.next(1, 4);
    println(tests);

    for (int tc = 0; tc < tests; ++tc) {
        int mode = rnd.next(0, 3);
        int columns;
        int rows;
        if (mode == 0) {
            columns = rnd.next(1, 6);
            rows = rnd.next(1, 5);
        } else if (mode == 1) {
            columns = rnd.next(24, 30);
            rows = rnd.next(1, 4);
        } else {
            columns = rnd.next(2, 12);
            rows = rnd.next(3, 8);
        }

        println(columns, rows);

        int cells = columns * rows;
        vector<string> tokens(cells);
        for (int i = 0; i < cells; ++i) {
            bool canFormula = i > 0;
            bool useFormula = canFormula && rnd.next(0, 99) < (mode == 2 ? 55 : 35);
            if (useFormula) {
                int maxRefs = min(4, i);
                int refs = rnd.next(1, maxRefs);
                if (rnd.next(0, 99) < 20) refs = 1;
                tokens[i] = makeFormula(i, columns, refs);
            } else {
                int valueMode = rnd.next(0, 4);
                if (valueMode == 0) {
                    tokens[i] = toString(rnd.next(-5, 5));
                } else if (valueMode == 1) {
                    tokens[i] = toString(rnd.next(-100, 100));
                } else if (valueMode == 2) {
                    tokens[i] = toString(rnd.next(0, 1) == 0 ? -100000 : 100000);
                } else {
                    tokens[i] = toString(rnd.next(-1000, 1000));
                }
            }
        }

        for (int row = 0; row < rows; ++row) {
            vector<string> line;
            for (int column = 0; column < columns; ++column) {
                line.push_back(tokens[row * columns + column]);
            }
            println(line);
        }
    }

    return 0;
}
