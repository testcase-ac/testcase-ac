#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, the number of plots
    int N = inf.readInt(1, 50000, "N");
    inf.readEoln();

    // For each plot, read W_i and H_i
    for (int i = 0; i < N; i++) {
        int W = inf.readInt(1, 1000000, "W_i");
        inf.readSpace();
        int H = inf.readInt(1, 1000000, "H_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
