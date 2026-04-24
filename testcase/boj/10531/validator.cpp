#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of knob distances
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read each knob distance
    for (int i = 0; i < N; i++) {
        inf.readInt(1, 200000, "k_i");
        inf.readEoln();
    }

    // Read number of holes
    int M = inf.readInt(1, 200000, "M");
    inf.readEoln();

    // Read each hole distance
    for (int j = 0; j < M; j++) {
        inf.readInt(1, 200000, "d_j");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
