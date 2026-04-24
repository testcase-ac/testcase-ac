#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read L and R according to problem constraints
    long long L = inf.readLong(0LL, 2147483647LL, "L");
    inf.readSpace();
    long long R = inf.readLong(0LL, 2147483647LL, "R");
    inf.readEoln();

    // Ensure L <= R
    ensuref(L <= R, "L (%lld) must be <= R (%lld)", L, R);

    inf.readEof();
    return 0;
}
