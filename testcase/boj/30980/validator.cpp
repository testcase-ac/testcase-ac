#include "testlib.h"

#include <string>

using namespace std;

bool isDigit(char ch) {
    return '0' <= ch && ch <= '9';
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 70, "N");
    inf.readSpace();
    int m = inf.readInt(1, 70, "M");
    inf.readEoln();

    int height = 3 * n;
    int width = 8 * m;

    for (int r = 0; r < height; ++r) {
        string row = inf.readLine("[^]*", "row");
        ensuref((int)row.size() == width, "row %d has length %d, expected %d",
                r + 1, (int)row.size(), width);

        for (int c = 0; c < width; ++c) {
            int localRow = r % 3;
            int localCol = c % 8;

            if (localRow != 1) {
                ensuref(row[c] == '.', "cell (%d,%d) must be margin '.'", r + 1, c + 1);
                continue;
            }

            if (localCol == 1 || localCol == 3 || localCol == 5) {
                ensuref(isDigit(row[c]), "cell (%d,%d) must be a digit", r + 1, c + 1);
            } else if (localCol == 2) {
                ensuref(row[c] == '+', "cell (%d,%d) must be '+'", r + 1, c + 1);
            } else if (localCol == 4) {
                ensuref(row[c] == '=', "cell (%d,%d) must be '='", r + 1, c + 1);
            } else if (localCol == 6) {
                ensuref(row[c] == '.' || isDigit(row[c]),
                        "cell (%d,%d) must be '.' or a digit", r + 1, c + 1);
                if (isDigit(row[c])) {
                    ensuref(row[c - 1] != '0',
                            "two-digit c in block ending at cell (%d,%d) has a leading zero",
                            r + 1, c + 1);
                }
            } else {
                ensuref(row[c] == '.', "cell (%d,%d) must be margin '.'", r + 1, c + 1);
            }
        }
    }

    inf.readEof();
}
