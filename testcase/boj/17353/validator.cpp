#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    // Read initial array A of size N
    vector<int> A = inf.readInts(n, 0, 1000000, "A_i");
    inf.readEoln();

    // Read number of queries Q
    int q = inf.readInt(1, 100000, "q");
    inf.readEoln();

    // Read Q queries
    for (int i = 0; i < q; i++) {
        int t = inf.readInt(1, 2, "type_i");
        if (t == 1) {
            // Update query: "1 L R"
            inf.readSpace();
            int L = inf.readInt(1, n, "L_i");
            inf.readSpace();
            int R = inf.readInt(L, n, "R_i");
            // R >= L is ensured by bounds on readInt for R
        } else {
            // Query type 2: "2 X"
            inf.readSpace();
            int X = inf.readInt(1, n, "X_i");
        }
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
