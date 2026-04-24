#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A and K
    int A = inf.readInt(1, 1000000, "A");
    inf.readSpace();
    int K = inf.readInt(1, 1000000, "K");
    inf.readEoln();

    // Validate A < K
    ensuref(A < K, "A (%d) must be strictly less than K (%d)", A, K);

    // No more data
    inf.readEof();
    return 0;
}
