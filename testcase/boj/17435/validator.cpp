#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read m
    int m = inf.readInt(1, 200000, "m");
    inf.readEoln();

    // Read the function values f(1) ... f(m)
    vector<int> f = inf.readInts(m, 1, m, "f_i");
    inf.readEoln();

    // Read number of queries Q
    int Q = inf.readInt(1, 200000, "Q");
    inf.readEoln();

    // Read each query (n, x)
    for (int i = 0; i < Q; i++) {
        int n = inf.readInt(1, 500000, "n_i");
        inf.readSpace();
        int x = inf.readInt(1, m, "x_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
