#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 30, "N");
    inf.readSpace();
    int M = inf.readInt(1, 30, "M");
    inf.readEoln();

    // Read pre-vaccine grid
    vector<vector<int>> pre(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        pre[i] = inf.readInts(M, 1, 1000, "pre[i][j]");
        inf.readEoln();
    }

    // Read post-vaccine grid
    vector<vector<int>> post(N, vector<int>(M));
    for (int i = 0; i < N; ++i) {
        post[i] = inf.readInts(M, 1, 1000, "post[i][j]");
        inf.readEoln();
    }

    inf.readEof();
}
