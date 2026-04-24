#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read m and n: 0 ≤ m ≤ n ≤ 1e6
    int m = inf.readInt(0, 1000000, "m");
    inf.readSpace();
    int n = inf.readInt(0, 1000000, "n");
    ensuref(m <= n, "Constraint violation: m (%d) must be ≤ n (%d)", m, n);
    inf.readEoln();

    // Each vertex can have at most one outgoing edge
    vector<char> has_out(n, 0);
    for (int i = 0; i < m; i++) {
        int v = inf.readInt(0, n - 1, "v_i");
        inf.readSpace();
        int w = inf.readInt(0, n - 1, "w_i");
        inf.readEoln();

        ensuref(!has_out[v],
                "Vertex %d has more than one outgoing edge", v);
        has_out[v] = 1;
    }

    inf.readEof();
    return 0;
}
