#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(1LL, 8589934591LL, "N");
    inf.readEoln();
    inf.readEof();
}
