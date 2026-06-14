#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(3, 20, "n");
    inf.readSpace();
    int m = inf.readInt(3, 20, "m");
    inf.readEoln();

    int a = inf.readInt(1, 1000, "a");
    inf.readSpace();
    int b = inf.readInt(1, 1000, "b");
    inf.readEoln();

    string rowPattern = "[#.]{";
    rowPattern += to_string(m);
    rowPattern += "}";
    for (int i = 0; i < n; ++i) {
        inf.readToken(rowPattern, "row");
        inf.readEoln();
    }

    inf.readEof();
}
