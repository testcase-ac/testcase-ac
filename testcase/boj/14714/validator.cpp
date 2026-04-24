#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, A, B, D_A, D_B
    int N = inf.readInt(2, 500, "N");
    inf.readSpace();
    int A = inf.readInt(1, N, "A");
    inf.readSpace();
    int B = inf.readInt(1, N, "B");
    ensuref(A != B, "A and B must be different: A=%d, B=%d", A, B);
    inf.readSpace();
    int DA = inf.readInt(1, N - 1, "D_A");
    inf.readSpace();
    int DB = inf.readInt(1, N - 1, "D_B");
    inf.readEoln();

    inf.readEof();
    return 0;
}
