#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readToken("order|chaos", "S");
    inf.readSpace();
    inf.readInt(2, 888888, "N");
    inf.readEoln();
    inf.readEof();
}
