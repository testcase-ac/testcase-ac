#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 1000000, "m");
    inf.readSpace();
    int k = inf.readInt(1, 1000, "k");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        std::string type = inf.readToken("R|S", "type");
        inf.readSpace();
        if (type == "R") {
            inf.readInt(1, n, "x");
        } else {
            inf.readInt(1, m, "x");
        }
        inf.readSpace();
        inf.readInt(0, 1000000000, "y");
        inf.readEoln();
    }

    inf.readEof();
}
