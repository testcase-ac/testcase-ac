#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readToken("1/4|1/2|3/4", "slice");
        inf.readEoln();
    }

    inf.readEof();
}
