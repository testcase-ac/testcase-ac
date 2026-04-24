#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read sequence A_1 ... A_N
    vector<int> A = inf.readInts(N, 1, 100000, "A_i");
    inf.readEoln();

    // Read number of queries M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read each query and validate 1 ≤ i ≤ j ≤ N
    for (int qi = 0; qi < M; qi++) {
        int i = inf.readInt(1, N, "i");
        inf.readSpace();
        int j = inf.readInt(1, N, "j");
        inf.readEoln();
        ensuref(i <= j, "Query %d has invalid range: i (%d) > j (%d)", qi + 1, i, j);
    }

    inf.readEof();
    return 0;
}
