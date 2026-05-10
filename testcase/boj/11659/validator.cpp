#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read the sequence of N numbers
    vector<int> a = inf.readInts(N, 1, 1000, "a_i");
    inf.readEoln();

    // Read M queries
    for (int qi = 0; qi < M; ++qi) {
        int i = inf.readInt(1, N, "i");
        inf.readSpace();
        int j = inf.readInt(1, N, "j");
        inf.readEoln();
        ensuref(i <= j,
                "Query %d is invalid: i (%d) > j (%d)",
                qi + 1, i, j);
    }

    inf.readEof();
    return 0;
}
