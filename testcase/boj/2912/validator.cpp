#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N and C
    int N = inf.readInt(3, 300000, "N");
    inf.readSpace();
    int C = inf.readInt(1, 10000, "C");
    inf.readEoln();

    // Second line: N colors
    vector<int> colors = inf.readInts(N, 1, C, "color");
    inf.readEoln();

    // Third line: M queries
    int M = inf.readInt(1, 10000, "M");
    inf.readEoln();

    // Next M lines: queries [A, B]
    for (int i = 0; i < M; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        ensuref(A <= B,
                "Query %d has A_i > B_i (%d > %d)",
                i + 1, A, B);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
