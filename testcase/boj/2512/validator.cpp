#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of regions N
    int N = inf.readInt(3, 10000, "N");
    inf.readEoln();

    // Read budget requests
    vector<int> budgets = inf.readInts(N, 1, 100000, "budget");
    inf.readEoln();

    // Read total budget M (must be at least N)
    long long M = inf.readLong((long long)N, 1000000000LL, "M");
    inf.readEoln();

    // No extra input
    inf.readEof();
    return 0;
}
