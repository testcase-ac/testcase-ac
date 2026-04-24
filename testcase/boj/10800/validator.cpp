#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of balls N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // For each ball, read its color C_i and size S_i
    for (int i = 0; i < N; i++) {
        int C = inf.readInt(1, N, "C_i");
        inf.readSpace();
        int S = inf.readInt(1, 2000, "S_i");
        inf.readEoln();
    }

    // Ensure no extra data
    inf.readEof();
    return 0;
}
