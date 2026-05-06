#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(2, 1000000, "N");
    inf.readEoln();

    // Read N lines, each Ai
    for (int i = 0; i < N; ++i) {
        int Ai = inf.readInt(0, (1 << 24) - 1, "A_i");
        inf.readEoln();
        (void)Ai; // suppress unused variable warning
    }

    inf.readEof();
}
