#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of cities N and number of bus routes M
    int N = inf.readInt(1, 500, "N");
    inf.readSpace();
    int M = inf.readInt(1, 6000, "M");
    inf.readEoln();

    // Read each bus route: A, B, C
    for (int i = 0; i < M; i++) {
        int A = inf.readInt(1, N, "A_i");
        inf.readSpace();
        int B = inf.readInt(1, N, "B_i");
        inf.readSpace();
        int C = inf.readInt(-10000, 10000, "C_i");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
