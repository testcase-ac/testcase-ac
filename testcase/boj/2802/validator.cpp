#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(2, 100000, "N");
    inf.readSpace();
    int K = inf.readInt(2, N, "K");
    inf.readEoln();

    // Read N crayons, each with R, G, B in [0,255]
    for (int i = 0; i < N; i++) {
        inf.readInt(0, 255, "R_i");
        inf.readSpace();
        inf.readInt(0, 255, "G_i");
        inf.readSpace();
        inf.readInt(0, 255, "B_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
