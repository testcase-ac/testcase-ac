#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and D
    int N = inf.readInt(1, 40000, "N");
    inf.readSpace();
    int D = inf.readInt(1, 50000, "D");
    inf.readEoln();

    // Read initial outputs M[1..N]
    for (int i = 1; i <= N; i++) {
        inf.readInt(1, 100000, "M_i");
        inf.readEoln();
    }

    // Read D updates: each day one update (idx, new value)
    for (int d = 1; d <= D; d++) {
        inf.readInt(1, N, "update_index");
        inf.readSpace();
        inf.readInt(1, 100000, "update_value");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
