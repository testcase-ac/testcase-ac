#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 15, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readToken("[BW]{" + std::to_string(n) + "}", "row");
        inf.readEoln();
    }

    inf.readEof();
}
