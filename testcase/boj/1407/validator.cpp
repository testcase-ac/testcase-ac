#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long a = inf.readLong(1LL, 1000000000000000LL, "A");
    inf.readSpace();
    long long b = inf.readLong(a, 1000000000000000LL, "B");
    inf.readEoln();

    inf.readEof();
}
