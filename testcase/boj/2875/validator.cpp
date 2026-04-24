#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K with strict spacing
    int N = inf.readInt(0, 100, "N");
    inf.readSpace();
    int M = inf.readInt(0, 100, "M");
    inf.readSpace();
    // K must satisfy 0 <= K <= N+M
    int K = inf.readInt(0, N + M, "K");
    inf.readEoln();

    // End of file immediately after the single line
    inf.readEof();
    return 0;
}
