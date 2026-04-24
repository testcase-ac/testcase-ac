#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: A, B, C, D
    int A = inf.readInt(1, 999, "A");
    inf.readSpace();
    int B = inf.readInt(1, 999, "B");
    inf.readSpace();
    int C = inf.readInt(1, 999, "C");
    inf.readSpace();
    int D = inf.readInt(1, 999, "D");
    inf.readEoln();

    // Second line: P, M, N
    int P = inf.readInt(1, 999, "P");
    inf.readSpace();
    int M = inf.readInt(1, 999, "M");
    inf.readSpace();
    int N = inf.readInt(1, 999, "N");
    inf.readEoln();

    // No extra tokens
    inf.readEof();
    return 0;
}
