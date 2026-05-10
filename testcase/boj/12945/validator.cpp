#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 500000, "N");
    inf.readEoln();

    // Read N lines of V[i]
    for (int i = 0; i < N; ++i) {
        int V = inf.readInt(1, 100000, "V_i");
        inf.readEoln();
    }

    inf.readEof();
}
