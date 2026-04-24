#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, the number of participants
    int N = inf.readInt(2, 500000, "N");
    inf.readSpace();

    // Read A and B, the initial token holders (must be distinct)
    int A = inf.readInt(1, N, "A");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    inf.readSpace();
    ensuref(A != B, "A and B must be different, but both are %d", A);

    // Read D_A and D_B, the step sizes for token A and B
    int DA = inf.readInt(1, N - 1, "D_A");
    inf.readSpace();
    int DB = inf.readInt(1, N - 1, "D_B");

    inf.readEoln();
    inf.readEof();
    return 0;
}
