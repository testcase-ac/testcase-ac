#include "testlib.h"

#include <set>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(2, 1000, "R");
    inf.readSpace();
    int c = inf.readInt(2, 1000, "C");
    inf.readEoln();

    vector<string> rows;
    rows.reserve(r);
    string rowPattern = "[a-z]{" + to_string(c) + "," + to_string(c) + "}";
    for (int i = 0; i < r; ++i) {
        rows.push_back(inf.readToken(rowPattern, "row"));
        inf.readEoln();
    }

    set<string> columns;
    for (int col = 0; col < c; ++col) {
        string current;
        current.reserve(r);
        for (int row = 0; row < r; ++row) {
            current.push_back(rows[row][col]);
        }
        ensuref(columns.insert(current).second,
                "duplicate full column ending at column %d", col + 1);
    }

    inf.readEof();
}
