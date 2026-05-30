#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 5, "R");
    inf.readSpace();
    int c = inf.readInt(1, 5, "C");
    inf.readSpace();
    inf.readInt(1, r * c, "K");
    inf.readEoln();

    for (int row = 0; row < r; ++row) {
        string line = inf.readToken("[.T]{" + to_string(c) + "}", "map_row");
        ensuref((int)line.size() == c, "row %d must have exactly %d cells", row + 1, c);
        if (row == 0) {
            ensuref(line[c - 1] == '.', "barn cell must be empty");
        }
        if (row == r - 1) {
            ensuref(line[0] == '.', "starting cell must be empty");
        }
        inf.readEoln();
    }

    inf.readEof();
}
