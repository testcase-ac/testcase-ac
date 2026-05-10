#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and L
    int N = inf.readInt(1, 50000, "N");
    inf.readSpace();
    int L = inf.readInt(1, 1000000000, "L");
    inf.readEoln();

    vector<int> x(N);
    set<int> xset;
    vector<int> d(N);
    vector<int> w(N);

    for (int i = 0; i < N; ++i) {
        w[i] = inf.readInt(1, 1000, "w_i");
        inf.readSpace();
        x[i] = inf.readInt(1, L-1, "x_i");
        inf.readSpace();
        d[i] = inf.readInt(-1, 1, "d_i");
        inf.readEoln();

        ensuref(d[i] == 1 || d[i] == -1, "d_i at line %d must be 1 or -1, got %d", i+2, d[i]);
        ensuref(xset.count(x[i]) == 0, "x_i at line %d is not unique: %d", i+2, x[i]);
        xset.insert(x[i]);
    }

    // Check all x_i are distinct and in (0, L)
    // Already checked above.

    // No further global properties to check (e.g., no guarantee about answer, or about meetings always existing, etc.)

    inf.readEof();
}
