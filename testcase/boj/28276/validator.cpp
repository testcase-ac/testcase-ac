#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int r = inf.readInt(1, 1000000, "R");
    inf.readSpace();
    int c = inf.readInt(1, 1000000, "C");
    inf.readSpace();
    int w = inf.readInt(0, c - 1, "W");
    inf.readEoln();

    ensuref(1LL * r * c <= 1000000LL, "R*C must be at most 1000000");

    string rowPattern = "[01]{" + to_string(c) + "}";
    for (int i = 0; i < r; ++i) {
        inf.readToken(rowPattern, "row");
        inf.readEoln();
    }

    inf.readEof();
}
