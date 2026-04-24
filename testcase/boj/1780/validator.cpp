#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 2187, "N");
    // N must be 3^k for some k in [0,7]
    {
        static const int powers_of_3[] = {1, 3, 9, 27, 81, 243, 729, 2187};
        bool ok = false;
        for (int p : powers_of_3) {
            if (N == p) { ok = true; break; }
        }
        ensuref(ok, "N must be a power of 3 (up to 3^7), got %d", N);
    }
    inf.readEoln();

    // Read the matrix
    for (int i = 0; i < N; i++) {
        // Each row has exactly N integers in {-1,0,1}
        inf.readInts(N, -1, 1, "matrix");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
