#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read array A of length N
    vector<int> A = inf.readInts(N, -1000, 1000, "A_i");
    inf.readEoln();

    // Read M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // Read M queries
    for (int q = 0; q < M; q++) {
        int i = inf.readInt(1, N, "i");
        inf.readSpace();
        int j = inf.readInt(1, N, "j");
        inf.readEoln();
        ensuref(j >= i,
                "Invalid query at line %d: j (%d) < i (%d)",
                q + 1, j, i);
    }

    // No extra content
    inf.readEof();
    return 0;
}
