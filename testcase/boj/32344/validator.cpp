#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read grid dimensions
    int R = inf.readInt(1, 100000, "R");
    inf.readSpace();
    int C = inf.readInt(1, 100000, "C");
    inf.readEoln();

    // Read number of pieces
    int N = inf.readInt(1, 100000, "N");
    inf.readEoln();

    // Read each piece information
    for (int i = 0; i < N; i++) {
        int a = inf.readInt(1, N, "a_i");
        inf.readSpace();
        int v = inf.readInt(1, R, "v_i");
        inf.readSpace();
        int h = inf.readInt(1, C, "h_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
