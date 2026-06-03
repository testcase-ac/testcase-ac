#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int s = inf.readInt(1, 50, "S");
    inf.readSpace();
    inf.readInt(1, s, "dotorya");
    inf.readSpace();
    inf.readInt(1, s, "kesakiyo");
    inf.readSpace();
    inf.readInt(1, s, "hongjun7");
    inf.readEoln();
    inf.readEof();
}
