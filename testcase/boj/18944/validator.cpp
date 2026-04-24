#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and T
    int N = inf.readInt(1, 500000, "N");
    inf.readSpace();
    int T = inf.readInt(1, 500000, "T");
    inf.readEoln();

    // Read array A of length N
    vector<int> A = inf.readInts(N, 1, 1000000000, "A_i");
    inf.readEoln();

    // Read T queries (L_i, R_i)
    for (int i = 0; i < T; i++) {
        int L = inf.readInt(1, N, "L_i");
        inf.readSpace();
        int R = inf.readInt(1, N, "R_i");
        ensuref(L <= R,
                "For query %d, L_i = %d is greater than R_i = %d",
                i + 1, L, R);
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
