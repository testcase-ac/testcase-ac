#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read T and W
    int T = inf.readInt(1, 1000, "T");
    inf.readSpace();
    int W = inf.readInt(1, 30, "W");
    inf.readEoln();

    // Read T lines of falling tree indices (1 or 2)
    for (int i = 0; i < T; i++) {
        int x = inf.readInt(1, 2, "tree_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
