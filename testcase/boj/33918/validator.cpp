#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, C, D
    int N = inf.readInt(1, 200, "N");
    inf.readSpace();
    int M = inf.readInt(1, 25000, "M");
    inf.readSpace();
    int C = inf.readInt(1, M, "C");
    inf.readSpace();
    int D = inf.readInt(C, M, "D");
    inf.readEoln();

    // D is a multiple of C
    ensuref(D % C == 0, "D (%d) must be a multiple of C (%d)", D, C);

    // Read b_0 ... b_{N-1}
    std::vector<int> b = inf.readInts(N, 1, M, "b_i");
    inf.readEoln();

    inf.readEof();
}
