#include "testlib.h"

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K
    int N = inf.readInt(2, 8, "N");
    inf.readSpace();
    int M = inf.readInt(1, N - 1, "M");
    inf.readSpace();
    int K = inf.readInt(1, M, "K");
    inf.readEoln();

    inf.readEof();
}
