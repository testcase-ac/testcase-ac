#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 999999, "A");
    inf.readSpace();
    int b = inf.readInt(a + 1, 1000000, "B");
    inf.readSpace();
    inf.readInt(2, 100, "K");
    inf.readEoln();
    inf.readEof();
}
