#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 200, "n");
    inf.readSpace();
    int m = inf.readInt(1, 200, "m");
    inf.readEoln();

    const string rowPattern = "[A-Z]{" + to_string(m) + "}";
    for (int i = 0; i < n; ++i) {
        inf.readToken(rowPattern, "board_row");
        inf.readEoln();
    }

    inf.readEof();
}
