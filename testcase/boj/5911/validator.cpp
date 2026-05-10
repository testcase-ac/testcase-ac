#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and B
    int N = inf.readInt(1, 1000, "N");
    inf.readSpace();
    int B = inf.readInt(1, 1000000000, "B");
    inf.readEoln();

    // Read N lines of P(i) and S(i)
    for (int i = 0; i < N; ++i) {
        int P = inf.readInt(0, 1000000000, "P_i");
        inf.readSpace();
        int S = inf.readInt(0, 1000000000, "S_i");
        inf.readEoln();
    }

    inf.readEof();
}
