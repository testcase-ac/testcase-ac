#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long MIN_COUNT = 0LL;
    const long long MAX_COUNT = 1000000000LL;

    inf.readLong(MIN_COUNT, MAX_COUNT, "M_W");
    inf.readSpace();
    inf.readLong(MIN_COUNT, MAX_COUNT, "M_B");
    inf.readEoln();

    inf.readLong(MIN_COUNT, MAX_COUNT, "T_W");
    inf.readSpace();
    inf.readLong(MIN_COUNT, MAX_COUNT, "T_B");
    inf.readEoln();

    inf.readLong(MIN_COUNT, MAX_COUNT, "P_W");
    inf.readSpace();
    inf.readLong(MIN_COUNT, MAX_COUNT, "P_B");
    inf.readEoln();

    inf.readEof();
}
