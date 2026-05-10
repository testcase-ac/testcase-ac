#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of computers
    int n = inf.readInt(1, 100, "n");
    inf.readEoln();

    // Number of directly connected pairs
    // No explicit bound in statement, but we cap at 100000 to keep input size reasonable.
    int m = inf.readInt(0, 100000, "m");
    inf.readEoln();

    // Each connection is an undirected edge between two distinct computers (1..n).
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, n, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, n, "v_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
