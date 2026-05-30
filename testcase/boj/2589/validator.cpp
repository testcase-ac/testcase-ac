#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int H = inf.readInt(1, 50, "H");
    inf.readSpace();
    int W = inf.readInt(1, 50, "W");
    inf.readEoln();

    string rowPattern = "[LW]{" + to_string(W) + "}";
    int landCount = 0;
    for (int i = 0; i < H; i++) {
        string row = inf.readToken(rowPattern, "row");
        inf.readEoln();
        for (char cell : row) {
            if (cell == 'L') {
                landCount++;
            }
        }
    }
    ensuref(landCount >= 2, "map must contain at least two land cells");

    inf.readEof();
    return 0;
}
