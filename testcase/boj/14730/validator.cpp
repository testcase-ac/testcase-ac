#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of terms N
    int N = inf.readInt(1, 100, "N");
    inf.readEoln();

    vector<int> deg(N);
    for (int i = 0; i < N; i++) {
        // Read coefficient C
        int C = inf.readInt(-100, 100, "C_i");
        ensuref(C != 0, "Coefficient C at term %d must be non-zero, found 0", i+1);
        inf.readSpace();
        // Read degree K
        int K = inf.readInt(0, 1000, "K_i");
        deg[i] = K;
        inf.readEoln();
    }

    // Check that degrees are in strictly descending order (no duplicates, sorted)
    for (int i = 1; i < N; i++) {
        ensuref(deg[i-1] > deg[i],
                "Degrees must be in strictly descending order: term %d has degree %d not > degree %d of term %d",
                i, deg[i-1], deg[i], i+1);
    }

    inf.readEof();
    return 0;
}
