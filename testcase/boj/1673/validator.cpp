#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const long long N_MIN = 2;
    const long long N_MAX = 1000000000LL;
    const int TC_MAX = 100000;

    int tc = 0;
    // Read test cases until EOF
    while (!inf.eof()) {
        ++tc;
        ensuref(tc <= TC_MAX, "Too many test cases: %d (maximum %d)", tc, TC_MAX);

        // Read n and k
        long long n = inf.readLong(N_MIN, N_MAX, "n");
        inf.readSpace();
        long long k = inf.readLong(N_MIN, n, "k");
        inf.readEoln();
    }

    ensuref(tc > 0, "At least one test case expected");
    inf.readEof();
    return 0;
}
