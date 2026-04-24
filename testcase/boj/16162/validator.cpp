#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N, A, D
    int N = inf.readInt(1, 20000, "N");
    inf.readSpace();
    int A = inf.readInt(1, 10000000, "A");
    inf.readSpace();
    int D = inf.readInt(1, 10000000, "D");
    inf.readEoln();

    // Second line: N positive integers, each ≤ 1e7
    inf.readInts(N, 1, 10000000, "note_i");
    inf.readEoln();

    inf.readEof();
    return 0;
}
