#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    inf.readLong(-2147483648LL, 2147483647LL, "n");
    inf.readEoln();
    inf.readEof();
}
