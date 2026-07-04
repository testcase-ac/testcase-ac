#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long LIMIT = 1000000000000000000LL;

    inf.readLong(-LIMIT, LIMIT, "a_0");
    inf.readSpace();
    inf.readLong(-LIMIT, LIMIT, "b_0");
    inf.readEoln();
    inf.readEof();
}
