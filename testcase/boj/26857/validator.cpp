#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 1000, "R");
    inf.readSpace();
    int c = inf.readInt(1, 1000, "C");
    inf.readEoln();

    ensuref(1LL * r * c >= 2, "the board must contain at least 2 cells");

    int tokenCount = 0;
    for (int i = 0; i < r; ++i) {
        string row = inf.readLine("[a-z.]{1,1000}", "board_row");
        ensuref((int)row.size() == c,
                "row %d has length %d, expected %d", i + 1, (int)row.size(), c);
        for (char ch : row) {
            if (ch != '.') {
                ++tokenCount;
            }
        }
    }

    ensuref(tokenCount >= 1, "the board must contain at least one token");

    inf.readEof();
}
