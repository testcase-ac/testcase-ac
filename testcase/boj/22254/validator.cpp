#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and X
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int X = inf.readInt(1, 1000000000, "X");
    inf.readEoln();

    // Read processing times
    vector<int> t = inf.readInts(N, 1, X, "t_i");
    inf.readEoln();

    // No further global properties to check (e.g., no sum constraint, no ordering, etc.)
    // All constraints are per-value and already checked above.

    inf.readEof();
}
