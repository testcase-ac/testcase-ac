#include "testlib.h"
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int m = inf.readInt(1, 100, "m");
    inf.readSpace();
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    string rowPattern = "[RS]{" + to_string(n) + "}";
    for (int i = 0; i < m; ++i) {
        inf.readToken(rowPattern, "row");
        inf.readEoln();
    }

    inf.readEof();
}
