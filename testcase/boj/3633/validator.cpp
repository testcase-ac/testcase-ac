#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int k = inf.readInt(1, 1000, "k");
    inf.readEoln();

    for (int i = 1; i <= k; ++i) {
        setTestCase(i);
        inf.readInt(1, 1000000000, "n");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
