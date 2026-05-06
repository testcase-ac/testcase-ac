#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single test case: two integers n and k
    long long n = inf.readLong(0LL, 1000000000000LL, "n"); // 0 ≤ n ≤ 1e12
    inf.readSpace();
    long long k = inf.readLong(1LL, 1000000000000LL, "k"); // 1 ≤ k ≤ 1e12
    inf.readEoln();

    inf.readEof();
}
