#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "m");
    inf.readEoln();

    string rowPattern = "[BW]{" + to_string(m) + "," + to_string(m) + "}";
    for (int i = 0; i < n; ++i) {
        inf.readToken(rowPattern, "row");
        inf.readEoln();
    }

    inf.readEof();
}
