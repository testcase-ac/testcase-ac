#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(0LL, 4294967295LL, "n");
    inf.readEoln();
    inf.readEof();
}
