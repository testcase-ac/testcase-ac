#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices V and edges E
    int V = inf.readInt(1, 10000, "V");
    inf.readSpace();
    int E = inf.readInt(1, 100000, "E");
    inf.readEoln();

    // Read each undirected edge
    for (int i = 0; i < E; i++) {
        int A = inf.readInt(1, V, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, V, "B_i");
        inf.readEoln();
        // Loops or multiple edges are allowed by the statement, so no extra checks
    }

    inf.readEof();
    return 0;
}
