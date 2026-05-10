#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N and M
    int N = inf.readInt(1, 100000, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readEoln();

    // Read the N lecture lengths
    for (int i = 0; i < N; i++) {
        // Each length is a natural number ≤ 10000
        inf.readInt(1, 10000, "length");
        if (i + 1 < N) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    // No extra input
    inf.readEof();
    return 0;
}
