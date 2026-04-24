#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and check constraints
    int N = inf.readInt(1, 101, "N");
    ensuref(N % 2 == 1, "N must be odd, found %d", N);
    inf.readEoln();

    // Read N votes, each must be 0 or 1
    for (int i = 0; i < N; i++) {
        inf.readInt(0, 1, "vote");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
