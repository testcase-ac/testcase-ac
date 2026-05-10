#include "testlib.h"
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N
    int N = inf.readInt(1, 5000, "N");
    ensuref(N % 2 == 0, "N must be even, but got %d", N);
    inf.readEoln();

    // 2. Read A
    vector<int> A = inf.readInts(N, 1, 10000, "A_i");
    inf.readEoln();

    inf.readEof();
}
