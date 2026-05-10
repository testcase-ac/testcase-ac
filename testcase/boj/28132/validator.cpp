#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Read N vectors
    for (int i = 0; i < N; ++i) {
        int x = inf.readInt(-1000000000, 1000000000, "x_i");
        inf.readSpace();
        int y = inf.readInt(-1000000000, 1000000000, "y_i");
        inf.readEoln();
    }

    inf.readEof();
}
