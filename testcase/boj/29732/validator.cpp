#include "testlib.h"
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(1, 10000, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readSpace();
    int K = inf.readInt(0, N / 2, "K");
    inf.readEoln();

    // Read infection string S
    string S = inf.readToken("[.R]+", "S");
    ensuref((int)S.length() == N,
            "Length of S must be %d, but got %d", N, (int)S.length());
    // Characters are already constrained by regex to '.' or 'R'
    inf.readEoln();

    inf.readEof();
    return 0;
}
