#include "testlib.h"
#include <cassert>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and L
    int N = inf.readInt(1, 300000, "N");
    inf.readSpace();
    int L = inf.readInt(1, 300000, "L");
    inf.readEoln();

    // Read N lines of pairs (A_i, B_i)
    for (int i = 1; i <= N; i++) {
        int A = inf.readInt(1, L, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, L, "B_i");
        inf.readEoln();

        ensuref(A != B,
                "Constraint violated at line %d: A_i and B_i must differ, but both are %d",
                i + 1, A);
    }

    // No extra data
    inf.readEof();
    return 0;
}
