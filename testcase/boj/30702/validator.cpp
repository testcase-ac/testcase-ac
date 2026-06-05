#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 50, "n");
    inf.readSpace();
    int m = inf.readInt(3, 50, "m");
    inf.readEoln();

    string rowPattern = "[A-Z]{" + to_string(m) + "}";
    for (int i = 0; i < n; ++i) {
        inf.readToken(rowPattern, "a_row");
        inf.readEoln();
    }
    for (int i = 0; i < n; ++i) {
        inf.readToken(rowPattern, "b_row");
        inf.readEoln();
    }

    inf.readEof();
}
