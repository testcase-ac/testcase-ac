#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long n = inf.readLong(3LL, 1000000000LL, "N");
    inf.readSpace();
    long long a = inf.readLong(1LL, 1000000000LL, "a");
    inf.readEoln();

    inf.readEof();
}
