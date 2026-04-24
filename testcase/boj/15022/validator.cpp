#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of teams and events
    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 100000, "m");
    inf.readEoln();

    // Read each event: team t solves a problem with penalty p
    for (int i = 0; i < m; i++) {
        int t = inf.readInt(1, n, "t_i");
        inf.readSpace();
        int p = inf.readInt(1, 1000, "p_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
