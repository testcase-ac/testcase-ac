#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices V and edges E
    int V = inf.readInt(1, 20000, "V");
    inf.readSpace();
    int E = inf.readInt(1, 300000, "E");
    inf.readEoln();

    // Read starting vertex K
    int K = inf.readInt(1, V, "K");
    inf.readEoln();

    // Read E directed edges (u -> v with weight w)
    for (int i = 0; i < E; ++i) {
        int u = inf.readInt(1, V, "u");
        inf.readSpace();
        int v = inf.readInt(1, V, "v");
        inf.readSpace();
        int w = inf.readInt(1, 10, "w");
        inf.readEoln();

        // Validate no self-loop
        ensuref(u != v,
                "Loop detected at edge index %d: (%d -> %d)", i, u, v);
    }

    inf.readEof();
    return 0;
}
