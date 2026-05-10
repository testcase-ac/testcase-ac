#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readEoln();

    // To have at least one position to run (from M to N-M+1), we need N >= 2M-1
    ensuref((long long)N >= 2LL * M - 1,
            "N must be at least 2*M-1, but got N=%d, M=%d", N, M);

    // Read the intensities
    vector<int> a = inf.readInts(N, 1, 1000000, "intensity");
    inf.readEoln();

    inf.readEof();
    return 0;
}
