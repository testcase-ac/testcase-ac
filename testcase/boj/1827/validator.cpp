#include "testlib.h"
#include <cmath>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of people
    int N = inf.readInt(1, 8, "N");
    inf.readEoln();

    // Read guide's speed S (no explicit bound given in statement; we allow up to 1e6)
    inf.readDouble(0.0, 1e6, "S");
    inf.readEoln();

    const double PI = acos(-1.0);
    // Read each person's data
    for (int i = 0; i < N; i++) {
        // xi
        {
            char name[32];
            sprintf(name, "x_%d", i+1);
            inf.readDouble(-1e6, 1e6, name);
        }
        inf.readSpace();
        // yi
        {
            char name[32];
            sprintf(name, "y_%d", i+1);
            inf.readDouble(-1e6, 1e6, name);
        }
        inf.readSpace();
        // vi
        {
            char name[32];
            sprintf(name, "v_%d", i+1);
            inf.readDouble(1.0, 100.0, name);
        }
        inf.readSpace();
        // ai
        {
            char name[32];
            sprintf(name, "a_%d", i+1);
            inf.readDouble(1.0, 2.0 * PI, name);
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
