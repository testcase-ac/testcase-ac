#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    long long a = inf.readLong(1LL, 100000000000LL, "A");
    inf.readEoln();
    long long b = inf.readLong(a, 100000000000LL, "B");
    inf.readEoln();

    inf.readEof();
}
