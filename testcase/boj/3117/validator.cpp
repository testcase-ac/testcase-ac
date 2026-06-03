#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int MAX_N = 100000;
    const int MAX_K = 100000;
    const int MAX_M = 1000000000;

    int n = inf.readInt(1, MAX_N, "N");
    inf.readSpace();
    int k = inf.readInt(1, MAX_K, "K");
    inf.readSpace();
    // CHECK: The original Korean statement allows M = 1; the English variant says M > 1.
    inf.readInt(1, MAX_M, "M");
    inf.readEoln();

    inf.readInts(n, 1, k, "initial_video");
    inf.readEoln();

    inf.readInts(k, 1, k, "recommended_video");
    inf.readEoln();

    inf.readEof();
    return 0;
}
