#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int a = inf.readInt(1, 999999, "a");
    inf.readSpace();
    int b = inf.readInt(a + 1, 1000000, "b");
    inf.readEoln();
    inf.readEof();
}
