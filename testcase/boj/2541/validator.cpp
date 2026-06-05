#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100000, "a");
    inf.readSpace();
    inf.readInt(1, 100000, "b");
    inf.readEoln();

    for (int i = 1; i <= 5; ++i) {
        inf.readInt(1, 100000, "p");
        inf.readSpace();
        inf.readInt(1, 100000, "q");
        inf.readEoln();
    }

    inf.readEof();
}
