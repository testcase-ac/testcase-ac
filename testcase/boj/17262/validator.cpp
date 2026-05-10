#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of fans
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // For each fan, read their interval [s_i, e_i]
    for (int i = 0; i < N; i++) {
        int s = inf.readInt(1, 100000, "s_i");
        inf.readSpace();
        int e = inf.readInt(1, 100000, "e_i");
        inf.readEoln();
        ensuref(s <= e, "s_i (%d) must be <= e_i (%d) at line %d", s, e, i+2);
    }

    // No extra data
    inf.readEof();
    return 0;
}
