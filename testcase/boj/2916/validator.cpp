#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // First line: N and K
    int N = inf.readInt(1, 10, "N");
    inf.readSpace();
    int K = inf.readInt(1, 10, "K");
    inf.readEoln();

    // Second line: N base angles
    for (int i = 0; i < N; i++) {
        int a = inf.readInt(0, 359, "base_angle");
        if (i + 1 < N) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    // Third line: K query angles
    for (int i = 0; i < K; i++) {
        int q = inf.readInt(0, 359, "query_angle");
        if (i + 1 < K) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }
    }

    inf.readEof();
    return 0;
}
