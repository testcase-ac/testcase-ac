#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N, M, K with their bounds
    int N = inf.readInt(1, 1000000, "N");
    inf.readSpace();
    int M = inf.readInt(1, 1000000, "M");
    inf.readSpace();
    int K = inf.readInt(1, 1000000, "K");
    inf.readEoln();

    // Validate the implied constraint K <= N
    ensuref(K <= N, "K must be <= N, but N = %d, K = %d", N, K);

    inf.readEof();
    return 0;
}
