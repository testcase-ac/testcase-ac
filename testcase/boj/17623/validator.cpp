#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int t = inf.readInt(1, 100, "T");
    inf.readEoln();
    for (int i = 0; i < t; ++i) {
        setTestCase(i + 1);
        inf.readInt(5, 1000, "N");
        inf.readEoln();
    }
    inf.readEof();
}
