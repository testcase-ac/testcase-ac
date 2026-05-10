#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Single integer n, 1 ≤ n ≤ 500000
    // 2n is the number of vertices in the graph.
    // Canonical integer format is enforced automatically by readInt.
    int n = inf.readInt(1, 500000, "n");
    inf.readEoln();

    // No further structure in the input, the problem is to compute an answer
    // from this single parameter. There are no additional global properties
    // to validate (like existence of some structure in the input), since the
    // input does not contain a graph, only n.

    inf.readEof();
}
