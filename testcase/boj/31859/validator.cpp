#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 100, "N");
    inf.readSpace();
    inf.readToken("[a-z]{1,20}", "S");
    inf.readEoln();
    inf.readEof();
}
