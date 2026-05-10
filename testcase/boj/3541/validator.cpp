#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read n and m
    int n = inf.readInt(1, 1000000, "n");
    inf.readSpace();
    int m = inf.readInt(1, 2000, "m");
    inf.readEoln();

    // Read each elevator's up and down values
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(1, 1000, "u_i");
        inf.readSpace();
        int d = inf.readInt(1, 1000, "d_i");
        inf.readEoln();
    }

    // No extra data
    inf.readEof();
    return 0;
}
