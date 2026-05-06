#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer M, 1 ≤ M ≤ 2^30 - 1
    // 2^30 - 1 = 1073741823
    const int MAX_M = (1 << 30) - 1;

    // Read M, enforcing canonical integer format and range
    long long M = inf.readLong(1LL, (long long)MAX_M, "M");
    inf.readEoln();

    // No further global constraints implied in the statement:
    // - There is no explicit claim like "answer always exists" or
    //   bounds on N depending on M that must be verified by simulation.
    // - We only need to ensure the input format and numeric constraints.

    inf.readEof();
}
