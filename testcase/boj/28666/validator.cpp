#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test: two integers n and m
    // Constraints: 1 ≤ n ≤ 1e6, n ≤ m ≤ 5n
    long long n = inf.readLong(1LL, 1000000LL, "n");
    inf.readSpace();
    long long m = inf.readLong(n, 5LL * n, "m");
    inf.readEoln();

    inf.readEof();
}
