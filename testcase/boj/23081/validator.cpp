#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 500, "N");
    inf.readEoln();

    bool hasEmpty = false;
    string rowPattern = "[.WB]{" + to_string(n) + "}";
    for (int y = 0; y < n; ++y) {
        string row = inf.readToken(rowPattern, "row");
        inf.readEoln();
        for (char cell : row) {
            if (cell == '.') {
                hasEmpty = true;
            }
        }
    }

    ensuref(hasEmpty, "board must contain at least one empty cell");
    inf.readEof();
}
