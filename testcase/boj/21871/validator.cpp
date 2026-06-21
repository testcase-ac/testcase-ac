#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 1000000000LL, "n");
    inf.readSpace();
    inf.readLong(1LL, 1000000000LL, "k");
    inf.readEoln();
    inf.readEof();
}
