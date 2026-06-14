#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 2000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "M");
    inf.readSpace();
    int k = inf.readInt(1, n * m, "K");
    inf.readEoln();

    string rowPattern = "[O.]{" + to_string(m) + "," + to_string(m) + "}";
    for (int i = 0; i < n; ++i) {
        inf.readToken(rowPattern, "row");
        inf.readEoln();
    }

    inf.readEof();
}
