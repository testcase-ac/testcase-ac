#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 200, "N");
    inf.readSpace();
    int K = inf.readInt(1, 1000, "K");
    inf.readEoln();

    // Read the N x N grid
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            int v = inf.readInt(0, K, "virus");
            if (j + 1 < N) inf.readSpace();
        }
        inf.readEoln();
    }

    // Read S, X, Y
    int S = inf.readInt(0, 10000, "S");
    inf.readSpace();
    int X = inf.readInt(1, N, "X");
    inf.readSpace();
    int Y = inf.readInt(1, N, "Y");
    inf.readEoln();

    inf.readEof();
}
