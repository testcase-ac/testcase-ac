#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of queries T: 1 ≤ T ≤ 1000
    int T = inf.readInt(1, 1000, "T");
    inf.readEoln();

    // For each query, read N and M: both are natural numbers (≥1) and ≤ 1e9
    for (int i = 0; i < T; i++) {
        long long N = inf.readLong(1LL, 1000000000LL, "N");
        inf.readSpace();
        long long M = inf.readLong(1LL, 1000000000LL, "M");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
