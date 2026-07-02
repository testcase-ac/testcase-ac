#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readInt(1, 3000, "n");
    inf.readSpace();
    inf.readLong(0LL, 1000000000LL, "a");
    inf.readSpace();
    inf.readLong(0LL, 1000000000LL, "b");
    inf.readEoln();
    inf.readEof();
}
