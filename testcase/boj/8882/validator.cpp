#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of machines n and batteries per chip k
    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int k = inf.readInt(1, 1000000, "k");
    inf.readEoln();

    // Total batteries = 2 * n * k must not exceed 1e6
    long long total = 2LL * n * k;
    ensuref(total <= 1000000LL,
            "Total number of batteries must satisfy 2*n*k <= 1e6, but got 2*%d*%d = %lld",
            n, k, total);

    // Read the battery power outputs
    vector<int> p = inf.readInts((int)total, 1, 1000000000, "p_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
