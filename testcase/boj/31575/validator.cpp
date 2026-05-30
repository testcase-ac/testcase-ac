#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 300, "N");
    inf.readSpace();
    int M = inf.readInt(1, 300, "M");
    inf.readEoln();

    vector<vector<int>> a(M, vector<int>(N));

    for (int i = 0; i < M; ++i) {
        a[i] = inf.readInts(N, 0, 1, "cell");
        inf.readEoln();
    }

    ensuref(a[0][0] == 1, "top-left cell must be 1");
    ensuref(a[M - 1][N - 1] == 1, "bottom-right cell must be 1");

    inf.readEof();
}
