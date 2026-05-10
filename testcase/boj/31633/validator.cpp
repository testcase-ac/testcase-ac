#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N, M
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000, "M");
    inf.readEoln();

    // 2. Read S matrix
    vector<vector<int>> S(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        S[i] = inf.readInts(M, 1, 1000000000, "S[i][j]");
        inf.readEoln();
    }

    inf.readEof();
}
