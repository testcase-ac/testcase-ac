#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and K
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int K = inf.readInt(1, 100000, "K");
    inf.readEoln();

    // Read N items
    for (int i = 0; i < N; i++) {
        // Weight W_i and Value V_i
        int W = inf.readInt(1, 100000, "W_i");
        inf.readSpace();
        int V = inf.readInt(0, 1000, "V_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
