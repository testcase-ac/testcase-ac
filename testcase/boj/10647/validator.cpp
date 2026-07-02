#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 500, "R");
    inf.readSpace();
    int s = inf.readInt(1, 500, "S");
    inf.readEoln();

    bool hasTree = false;
    for (int row = 1; row <= r; ++row) {
        string line = inf.readToken("[x.]{1,500}", "garden_row");
        inf.readEoln();

        ensuref((int)line.size() == s,
                "garden row %d has length %d, expected %d",
                row,
                (int)line.size(),
                s);
        for (char cell : line) {
            hasTree = hasTree || cell == 'x';
        }
    }
    ensuref(hasTree, "the initial garden must contain at least one tree");

    int g = inf.readInt(1, 100000, "G");
    inf.readEoln();

    for (int year = 1; year <= g; ++year) {
        inf.readInt(1, r, "r_i");
        inf.readSpace();
        inf.readInt(1, s, "s_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
