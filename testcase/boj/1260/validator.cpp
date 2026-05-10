#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, V
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 10000, "M");
    inf.readSpace();
    int V = inf.readInt(1, N, "V");
    inf.readEoln();

    // Read M undirected edges; loops and multiple edges are allowed by statement
    for (int i = 0; i < M; i++) {
        int u = inf.readInt(1, N, "u_i");
        inf.readSpace();
        int v = inf.readInt(1, N, "v_i");
        inf.readEoln();
        // No further constraints: loops (u==v) and duplicates allowed
    }

    inf.readEof();
    return 0;
}
