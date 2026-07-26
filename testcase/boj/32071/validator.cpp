#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 3000, "M");
    inf.readEoln();

    int white = 0;
    for (int i = 0; i < n; ++i) {
        string row = inf.readToken(format("[01]{%d}", m), format("row_%d", i + 1));
        inf.readEoln();
        for (char cell : row) {
            white += cell == '1';
        }
    }

    ensuref(white >= 2, "the grid must contain at least two white cells, got %d", white);
    inf.readEof();
}
