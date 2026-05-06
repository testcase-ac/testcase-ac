#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // n: number of black nodes and white nodes
    int n = inf.readInt(1, 300, "n");
    inf.readEoln();

    vector<string> red(n), blue(n);

    // Read red adjacency matrix
    for (int i = 0; i < n; ++i) {
        red[i] = inf.readLine("[01]{" + toString(n) + "}", "red_row");
        ensuref((int)red[i].size() == n,
                "Red adjacency row %d must have length %d, but has %d",
                i + 1, n, (int)red[i].size());
    }

    // Read blue adjacency matrix
    for (int i = 0; i < n; ++i) {
        blue[i] = inf.readLine("[01]{" + toString(n) + "}", "blue_row");
        ensuref((int)blue[i].size() == n,
                "Blue adjacency row %d must have length %d, but has %d",
                i + 1, n, (int)blue[i].size());
    }

    // Global constraint: no same-color parallel edges is already enforced
    // by adjacency matrix format (each pair has at most one red and one blue edge).

    // No further global guarantees (like existence of perfect matching) are
    // stated in the problem, so we do not validate such properties.

    inf.readEof();
}
