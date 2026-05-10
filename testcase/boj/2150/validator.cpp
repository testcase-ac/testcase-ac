#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of vertices and edges
    int V = inf.readInt(1, 10000, "V");
    inf.readSpace();
    int E = inf.readInt(1, 100000, "E");
    inf.readEoln();

    // Read E directed edges
    for (int i = 0; i < E; i++) {
        int a = inf.readInt(1, V, "A_i");
        inf.readSpace();
        int b = inf.readInt(1, V, "B_i");
        inf.readEoln();
        // Self-loops and multiple edges are allowed by problem statement
    }

    inf.readEof();
    return 0;
}
