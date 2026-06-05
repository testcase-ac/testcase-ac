#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int v = inf.readInt(1, 10000, "V");
    inf.readSpace();
    int e = inf.readInt(0, 100000, "E");
    inf.readEoln();

    for (int i = 0; i < e; ++i) {
        int u_i = inf.readInt(1, v, "u_i");
        inf.readSpace();
        int v_i = inf.readInt(1, v, "v_i");
        inf.readSpace();
        inf.readInt(1, 100000, "w_i");
        inf.readEoln();

        // CHECK: The statement explicitly allows parallel edges but does not
        // forbid self-loops, so only endpoint bounds are validated.
        (void)u_i;
        (void)v_i;
    }

    vector<int> route = inf.readInts(10, 1, v, "route_i");
    (void)route;
    inf.readEoln();

    inf.readInt(1, v, "start");
    inf.readEoln();
    inf.readEof();
}
