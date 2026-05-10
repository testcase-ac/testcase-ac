#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: four integers on one line
    long long X = inf.readLong(0LL, 1000000000LL, "X");
    inf.readSpace();
    long long Y = inf.readLong(0LL, 1000000000LL, "Y");
    inf.readSpace();
    long long W = inf.readLong(1LL, 10000LL, "W");
    inf.readSpace();
    long long S = inf.readLong(1LL, 10000LL, "S");
    inf.readEoln();

    // No additional global properties to validate:
    // - X,Y: non-negative integers <= 1e9
    // - W,S: positive integers <= 1e4
    // The problem does not guarantee any extra constraints like
    // reachability or bounded answer that need simulation checks.

    inf.readEof();
}
