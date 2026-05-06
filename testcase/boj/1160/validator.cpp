#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read 6 integers: m, a, c, X0, n, g
    long long m = inf.readLong(1LL, 1000000000000000000LL, "m"); // m: positive
    inf.readSpace();
    long long a = inf.readLong(0LL, 1000000000000000000LL, "a"); // a: non-negative
    inf.readSpace();
    long long c = inf.readLong(0LL, 1000000000000000000LL, "c"); // c: non-negative
    inf.readSpace();
    long long X0 = inf.readLong(0LL, 1000000000000000000LL, "X_0"); // X0: non-negative
    inf.readSpace();
    long long n = inf.readLong(1LL, 1000000000000000000LL, "n"); // n: positive
    inf.readSpace();
    long long g = inf.readLong(1LL, 100000000LL, "g"); // g: positive, up to 1e8
    inf.readEoln();

    // No further input
    inf.readEof();
}
