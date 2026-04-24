#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read V, P, L
    int V = inf.readInt(1, 250, "V");
    inf.readSpace();
    int P = inf.readInt(1, V, "P"); // 1 ≤ P ≤ V
    inf.readSpace();
    long long L = inf.readLong(1LL, 1000000000000LL, "L"); // 1 ≤ L ≤ 1e12
    inf.readEoln();

    // Read village positions
    vector<long long> x = inf.readLongs(V, 0LL, L - 1, "x_i");
    inf.readEoln();

    // Check non-decreasing order
    for (int i = 1; i < V; i++) {
        ensuref(x[i] >= x[i-1],
                "Village positions must be non-decreasing, but x[%d]=%lld > x[%d]=%lld",
                i-1, x[i-1], i, x[i]);
    }

    inf.readEof();
    return 0;
}
