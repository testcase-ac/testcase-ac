#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(2, 500, "N");
    inf.readSpace();
    int M = inf.readInt(1, 500, "M");
    inf.readEoln();

    // Read M statues
    for (int i = 0; i < M; i++) {
        int x = inf.readInt(1, N - 1, "X_i");
        inf.readSpace();
        int y = inf.readInt(1, N - 1, "Y_i");
        inf.readSpace();
        int v = inf.readInt(-100000, 100000, "V_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
