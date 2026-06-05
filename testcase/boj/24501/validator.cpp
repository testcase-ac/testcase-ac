#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 3000, "N");
    inf.readSpace();
    int m = inf.readInt(1, 3000, "M");
    inf.readEoln();

    string rowPattern = "[ESM]{" + to_string(m) + "}";
    for (int i = 1; i <= n; ++i) {
        inf.readToken(rowPattern, "ESM_i");
        inf.readEoln();
    }

    inf.readEof();
}
