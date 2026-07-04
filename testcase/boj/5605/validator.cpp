#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        int a = inf.readInt(1, 99, "a");
        inf.readSpace();
        int b = inf.readInt(a + 1, 100, "b");
        inf.readEoln();
    }

    inf.readEof();
}
