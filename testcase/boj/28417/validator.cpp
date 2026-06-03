#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    for (int i = 0; i < n; ++i) {
        inf.readInt(0, 100, "run1");
        inf.readSpace();
        inf.readInt(0, 100, "run2");
        for (int j = 0; j < 5; ++j) {
            inf.readSpace();
            inf.readInt(0, 100, "trick");
        }
        inf.readEoln();
    }

    inf.readEof();
}
