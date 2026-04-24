#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of tollgates and highways
    int n = inf.readInt(1, 200, "n");
    inf.readSpace();
    int m = inf.readInt(1, 20000, "m");
    inf.readEoln();

    // Read start and end tollgate
    int s = inf.readInt(1, n, "s");
    inf.readSpace();
    int t = inf.readInt(1, n, "t");
    inf.readEoln();

    // Read occupation costs for each tollgate
    for (int i = 1; i <= n; i++) {
        inf.readInt(1, 10000000, "cost");
        inf.readEoln();
    }

    // Read the highways (undirected edges)
    for (int i = 1; i <= m; i++) {
        inf.readInt(1, n, "u");
        inf.readSpace();
        inf.readInt(1, n, "v");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
