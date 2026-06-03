#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 50, "N");
    inf.readSpace();
    int m = inf.readInt(1, 50, "M");
    inf.readEoln();

    string rowPattern = "[a-zA-Z0-9\\.]{%d,%d}";
    rowPattern = format(rowPattern.c_str(), m, m);

    for (int i = 0; i < n; ++i) {
        inf.readLine(rowPattern, format("row_%d", i + 1));
    }

    inf.readEof();
}
