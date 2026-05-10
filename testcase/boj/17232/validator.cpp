#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N M T
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 100, "M");
    inf.readSpace();
    int T = inf.readInt(1, 300, "T");
    inf.readEoln();

    // Second line: K a b
    int K = inf.readInt(1, max(N, M), "K");
    inf.readSpace();
    int a = inf.readInt(0, (2*K+1)*(2*K+1)-1, "a");
    inf.readSpace();
    int b = inf.readInt(0, (2*K+1)*(2*K+1)-1, "b");
    inf.readEoln();

    // a, b constraint: 0 <= a, b < (2K+1)^2
    int max_neighbors = (2*K+1)*(2*K+1) - 1;
    ensuref(0 <= a && a < (2*K+1)*(2*K+1), "a (%d) out of range [0, (2K+1)^2-1] = [0, %d]", a, max_neighbors);
    ensuref(0 <= b && b < (2*K+1)*(2*K+1), "b (%d) out of range [0, (2K+1)^2-1] = [0, %d]", b, max_neighbors);

    // Next N lines: board
    for (int i = 0; i < N; ++i) {
        string row = inf.readLine("[.*]{"+to_string(M)+","+to_string(M)+"}", "board row");
        ensuref((int)row.size() == M, "Row %d: length is %d, expected %d", i+1, (int)row.size(), M);
        for (int j = 0; j < M; ++j) {
            ensuref(row[j] == '.' || row[j] == '*', "Row %d, Col %d: invalid character '%c', expected '.' or '*'", i+1, j+1, row[j]);
        }
    }

    inf.readEof();
}
