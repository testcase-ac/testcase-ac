#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K with exact spacing and line ending
    int N = inf.readInt(1, 500, "N");
    inf.readSpace();
    int M = inf.readInt(1, N, "M");
    inf.readSpace();
    int K = inf.readInt(1, N, "K");
    inf.readEoln();

    // No more input
    inf.readEof();
    return 0;
}
