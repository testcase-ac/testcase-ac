#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of queries M
    int M = inf.readInt(1, 100000, "M");
    inf.readEoln();

    // For each query, read N and K
    for (int i = 0; i < M; i++) {
        int N = inf.readInt(1, 4000000, "N");
        inf.readSpace();
        int K = inf.readInt(0, N, "K");
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}
